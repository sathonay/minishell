/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/08/22 18:57:31 by alrey            ###   ########.fr       */
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

void wait_commands(t_shell *shell, t_list *command_stack)
{
	t_command *command;

	while (command_stack)
	{
		command = command_stack->content;
		waitpid(command->pid, &shell->exit_code, 0);
		command_stack = command_stack->next;
	}
}

void executor(t_shell *shell, t_list *command_stack)
{
	t_command *command;

	while (command_stack)
	{
		command = command_stack->content;
		command->argc = ft_lstsize(command->argv_builder);
		command->argv = (char **) lst_to_array(command->argv_builder);
		ft_lstclear(&command->argv_builder, NULL);
		command->executable_path = find_exec(*command->argv, shell->env);
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
		command_stack = command_stack->next;
	}
	wait_commands(shell, shell->command_list);
}
