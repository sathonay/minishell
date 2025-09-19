/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/19 17:44:50 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_exit_status(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else
		return (128 + WTERMSIG(stat_loc));
}

static int	wait_commands(t_shell *shell)
{
	int			exit_code;
	int			stat_loc;
	int			n_command;
	t_list		*command_stack;
	t_command	last_command;

	exit_code = 0;
	if (!shell->command_list)
		return (-1);
	n_command = ft_lstsize(shell->command_list);
	command_stack = ft_lstlast(shell->command_list);
	if (!command_stack)
		return (-1);
	last_command = *((t_command *)command_stack->content);
	while (n_command--)
	{
		pid_t pid = wait(&stat_loc);
		dprintf(2, "exited %d %d\n", pid, stat_loc);
		if (pid == last_command.pid)
		{
			dprintf(2, "exited\n");
			exit_code = get_exit_status(stat_loc);
		}
	}
	return (exit_code);
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
	apply_redirections(command);
	close_redirections(shell->command_list);
	exit_code = builtin(shell, command);
	(dup2_close_old(fd_io_dup[0], 0), dup2_close_old(fd_io_dup[1], 1));
	return (exit_code);
}

static void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

static void	exec_fork(t_shell *shell, t_list *command_stack)
{
	int	(*builtin)(t_shell *, t_command);
	t_command *command;

	command = command_stack->content;
	command->pid = fork();
	if (command->pid != 0)
		return ;
	dprintf(2, "running %s\n", command->argv[0]);
	builtin = find_builtin(shell, command->argv[0]);
	if (builtin)
		exit(exec_builtin(builtin, shell, *command));
	command->executable_path = find_exec(*command->argv, shell->env);
	reset_signals();
	apply_redirections(*command);
	close_redirections(command_stack);
	if (command->executable_path)
		execve(command->executable_path, command->argv, shell->env);
	if (command->outfile.fd > 0 || command->infile.fd > 0)
		exit(0);
	printf("el minishello: command not found: %s\n", command->argv[0]);
	exit (127);
}

static void	execution(t_shell *shell, t_list *command_stack)
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
	if (command->prev_pipe[1] > 0)
		close(command->prev_pipe[1]);
	exec_fork(shell, command_stack);
	if (command->prev_pipe[0] > 0)
		close(command->prev_pipe[0]);
	if (command->next_pipe[1] > 0)
		close(command->next_pipe[1]);
	if (command_stack->next)
		execution(shell, command_stack->next);
}


void	executor(t_shell *shell, t_list *command_stack)
{
	execution(shell, command_stack);
	close_redirections(command_stack);
	shell->exit_code = wait_commands(shell);
	errno = 0;
	dprintf(2, "executor ended\n");
}
