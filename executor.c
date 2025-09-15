/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 12:22:06 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//MOVE TO lst_utils.c
static void	wait_commands(t_shell *shell, t_list *command_stack)
{
	t_command	*command;

	while (command_stack)
	{
		command = command_stack->content;
		if (command->pid)
			waitpid(command->pid, &shell->exit_code, 0);
		if (WIFEXITED(shell->exit_code))
			shell->exit_code = WEXITSTATUS(shell->exit_code);
		(close_fd(&command->infile.fd), close_fd(&command->outfile.fd));
		(close_pipe(command->prev_pipe, 2), close_pipe(command->next_pipe, 2));
		command_stack = command_stack->next;
	}
}

static int	exec_builtin(int (*builtin)(t_shell *, t_command),
				t_shell *shell, t_command command) {
	int	exit_code;
	int	fd_io_dup[2];

	fd_io_dup[0] = -1;
	fd_io_dup[1] = -1;
	if (command.prev_pipe[1] > 0 || command.infile.fd > 0)
		fd_io_dup[0] = dup(0);
	if (command.next_pipe[0] > 0 || command.outfile.fd > 0)
		fd_io_dup[1] = dup(1);
	apply_redirection(command);
	exit_code = builtin(shell, command);
	(dup2_close_old(fd_io_dup[0], 0), dup2_close_old(fd_io_dup[1], 1));
	return (exit_code);
}

static void	exec_fork(t_shell *shell, t_command *command)
{
	int	(*builtin)(t_shell *, t_command);

	command->pid = fork();
	if (command->pid != 0)
		return ;
	builtin = find_builtin(shell, command->argv[0]);
	if (builtin)
		exit(exec_builtin(builtin, shell, *command));
	command->executable_path = find_exec(*command->argv, shell->env);
	apply_redirection(*command);
	if (command->executable_path)
		execve(command->executable_path, command->argv, shell->env);
	if (command->outfile.fd > 0 || command->infile.fd > 0)
		exit(0);
	printf("el minishello: command not found: %s\n", command->argv[0]);
	exit (127);
}

static void	recursive_execution(t_shell *shell, t_list *command_stack)
{
	int			(*builtin)(t_shell *, t_command);
	t_command	*command;

	if (!command_stack)
		return ;
	command = command_stack->content;
	stack_args(command);
	here_is_the_doc(command);
	builtin = find_builtin(shell, command->argv[0]);
	if (builtin && command->next_pipe[0] <= 0 && command->prev_pipe[1] <= 0)
	{
		shell->exit_code = exec_builtin(builtin, shell, *command);
		return ;
	}
	if (command->next_pipe[1] > 0)
		recursive_execution(shell, command_stack->next);
	exec_fork(shell, command);
	if (command->prev_pipe[0] > 0)
		close(command->prev_pipe[0]);
	if (command->next_pipe[1] > 0)
		close(command->next_pipe[1]);
}

void	executor(t_shell *shell, t_list *command_stack)
{
	recursive_execution(shell, command_stack);
	wait_commands(shell, shell->command_list);
	errno = 0;
}
