/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/12 16:00:07 by alrey            ###   ########.fr       */
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

static void	*builtins(t_shell *shell, t_command *command)
{
	(void) shell;
	if (command->argv[0] == NULL)
		return (NULL);
	if (ft_strcmp(command->argv[0], "env") == 0)
		return (ft_env);
	if (ft_strcmp(command->argv[0], "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(command->argv[0], "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(command->argv[0], "exit") == 0)
		return (ft_exit);
	if (ft_strcmp(command->argv[0], "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(command->argv[0], "export") == 0)
		return (ft_export);
	if (ft_strcmp(command->argv[0], "unset") == 0)
		return (ft_unset);
	return (NULL);
}

static int	execution(t_shell *shell, t_command *command)
{
	int	(*builtin)(t_shell *, t_command);

	builtin = builtins(shell, command);
	command->executable_path = find_exec(*command->argv, shell->env);
	if (!builtin && command->executable_path)
		command->pid = fork();
	if (command->pid != 0)
		return (0);
	if (!builtin && !command->executable_path
		&& !command->infile.fd && !command->outfile.fd)
		printf("command not found: %s\n", *command->argv);
	if (!builtin && !command->executable_path
		&& !command->infile.fd && !command->outfile.fd)
		return (127);
	dup2_close_old(command->pipe[0], 0);
	dup2_close_old(command->infile.fd, 0);
	dup2_close_old(command->pipe[1], 1);
	dup2_close_old(command->outfile.fd, 1);
	if (!builtin && command->executable_path)
		execve(command->executable_path, command->argv, shell->env);
	else if (builtin)
		return (builtin(shell, *command));
	return (0);
}

void	executor(t_shell *shell, t_list *command_stack)
{
	t_command	*command;
	int			fd[2];

	while (command_stack)
	{
		command = command_stack->content;
		here_is_the_doc(command);
		dup_in_and_out(fd);
		command->argc = ft_lstsize(command->argv_builder);
		command->argv = (char **) lst_to_array(command->argv_builder);
		ft_lstclear(&command->argv_builder, NULL);
		if (command->infile.fd != -1 && command->outfile.fd != -1)
			shell->exit_code = execution(shell, command);
		else
			shell->exit_code = 1;
		close_fd(&command->pipe[0]);
		close_fd(&command->pipe[1]);
		close_fd(&command->infile.fd);
		close_fd(&command->outfile.fd);
		dup2_close_old(fd[0], 0);
		dup2_close_old(fd[1], 1);
		command_stack = command_stack->next;
	}
	wait_commands(shell, shell->command_list);
}
