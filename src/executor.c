/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/08/24 16:21:42 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static int get_command_count(t_token_stack *token) {
	int count;
	
	count = 1;
	while (token->type != NONE) {
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
}

static void tokens_to_commands(t_shell *shell) {
	t_token_stack *token;
	int command_count;

	token = shell->tokens;
	commands
	while (token)
	{
		printf("size %d\n", token->end - token->start);
		printf("type %d\n", token->type);
		write(1, token->start, token->end - token->start);
		write(1, "\n", 1);
		token = token->next;
	}
}*/

static void **lst_to_array(t_list *lst)
{
	size_t index;
	void	**array;

	index = 0;
	array = ft_calloc(ft_lstsize(lst) + 1, sizeof(void *));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[index] = lst->content;
		index++;
		lst = lst->next;
	}
	return (array);
}

static void	wait_commands(t_shell *shell, t_list *command_stack)
{
	t_command	*command;

	while (command_stack)
	{
		command = command_stack->content;
		if (command->pid)
		{
			command = command_stack->content;
			waitpid(command->pid, &shell->exit_code, 0);
		}
		if (command->infile.type == HERE_DOC)
			; // TODO remove heredoc file
		command_stack = command_stack->next;
	}
}

static void	here_is_the_doc(t_list *command_stack)
{
	t_command	*command;
	t_redirect	*infile;
	char		*line;

	while (command_stack)
	{
		command = command_stack->content;
		infile = &command->infile,
		line = NULL;
		if (infile->type == HERE_DOC)
		{
			line = readline("");
			while (line) {
				if (!line || ft_strncmp(line, infile->eof, ft_strlen(infile->eof)) == 0)
					break ;
				write(infile->fd, line, ft_strlen(line));
				write(infile->fd, "\n", 1);
				(free_str(&line), line = readline(""));
			}
			(free_str(&line), close(infile->fd));
			infile->fd = open(infile->path, O_CREAT | O_RDONLY, 0777);
		}
		command_stack = command_stack->next;
	}
}

static void	execution(t_shell *shell, t_command *command)
{
	command->pid = fork();
	if (command->pid == 0)
	{
		if (command->infile.fd != 0)
			dup2(command->infile.fd, 0);
		if (command->outfile.fd != 0)
			dup2(command->outfile.fd, 1);
		execve(command->executable_path, command->argv, shell->env);
	}
	if (command->infile.fd != 0)
		close(command->infile.fd);
	if (command->outfile.fd != 0)
		close(command->outfile.fd);
}

void	executor(t_shell *shell, t_list *command_stack)
{
	t_command	*command;

	here_is_the_doc(command_stack);
	while (command_stack)
	{
		command = command_stack->content;
		command->argc = ft_lstsize(command->argv_builder);
		command->argv = (char **) lst_to_array(command->argv_builder);
		ft_lstclear(&command->argv_builder, NULL);
		command->executable_path = find_exec(*command->argv, shell->env);
		if (command->executable_path)
			execution(shell, command);
		else
			printf("command not found: %s\n", *command->argv);
		command_stack = command_stack->next;
	}
	wait_commands(shell, shell->command_list);
}
