/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 21:25:38 by alrey            ###   ########.fr       */
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
		command_stack = command_stack->next;
	}
}

static void	here_is_the_doc(t_command *command)
{
	t_redirect	*infile;
	char		*line;

	infile = &command->infile;
	line = NULL;
	if (infile->type == HERE_DOC)
	{
		line = readline("");
		while (line)
		{
			if (!line
				|| ft_strncmp(line, infile->eof, ft_strlen(infile->eof)) == 0)
				break ;
			write(infile->fd, line, ft_strlen(line));
			write(infile->fd, "\n", 1);
			(free_str(&line), line = readline(""));
		}
		(free_str(&line), close(infile->fd));
		infile->fd = open(infile->path, O_CREAT | O_RDONLY, 0777);
	}
}

static int	exec_builtin(int (*builtin)(t_shell *, t_command),
				t_shell *shell, t_command command) {
	int	exit_code;
	int	fd_io_dup[2];

	fd_io_dup[0] = -1;
	fd_io_dup[1] = -1;
	if (command.pipe[0] > 0 || command.infile.fd > 0)
		fd_io_dup[0] = dup(0);
	if (command.pipe[1] > 0 || command.outfile.fd > 0)
		fd_io_dup[1] = dup(1);
	apply_redirection(command);
	exit_code = builtin(shell, command);
	(dup2_close_old(fd_io_dup[0], 0), dup2_close_old(fd_io_dup[1], 1));
	return (exit_code);
}

static int	execution(t_shell *shell, t_command *command)
{
	int	(*builtin)(t_shell *, t_command);

	builtin = find_builtin(shell, command->argv[0]);
	if (builtin)
		return (exec_builtin(builtin, shell, *command));
	command->executable_path = find_exec(*command->argv, shell->env);
	if (!command->executable_path
		&& (command->infile.fd > 0 || command->outfile.fd > 0))
		return (0);
	if (command->executable_path)
		command->pid = fork();
	if (command->pid != 0)
		return (0);
	if (!command->executable_path)
		return (printf("command not found: %s\n", *command->argv), 127);
	apply_redirection(*command);
	if (command->executable_path)
		execve(command->executable_path, command->argv, shell->env);
	return (0);
}

void	executor(t_shell *shell, t_list *command_stack)
{
	t_command	*command;

	while (command_stack)
	{
		command = command_stack->content;
		here_is_the_doc(command);
		command->argc = ft_lstsize(command->argv_builder);
		command->argv = (char **) lst_to_array(command->argv_builder);
		ft_lstclear(&command->argv_builder, NULL);
		if (command->infile.fd != -1 && command->outfile.fd != -1)
			shell->exit_code = execution(shell, command);
		else
			shell->exit_code = 1;
		(close_fd(&command->pipe[0]), close_fd(&command->infile.fd));
		(close_fd(&command->pipe[1]), close_fd(&command->outfile.fd));
		command_stack = command_stack->next;
	}
	wait_commands(shell, shell->command_list);
}
