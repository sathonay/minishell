/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:37:19 by alrey             #+#    #+#             */
/*   Updated: 2025/08/01 22:37:19 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

void	free_command(t_command *command)
{
	ft_lstclear(&command->argv_builder, free);
	free_str_array(command->argv);
}

static void pipe_it(t_shell *shell)
{
	t_command	*command;
	int			fd[2];
	command = (t_command *) ft_lstlast(shell->command_list)->content;
		
	if (command->outfile.type > 0)
	{
		printf("already outing");
		ft_lstadd_back(&shell->command_list,
			ft_lstnew(ft_calloc(sizeof(t_command), 1)));
		return;
	}
	printf("pipe_it\n");
	if (pipe(fd))
		return ;
	command->outfile.fd = fd[1];
	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	command = (t_command *) ft_lstlast(shell->command_list)->content;
	command->infile.fd = fd[0];
}

static t_token_stack	*handle_redirections(t_shell *shell, t_token_stack *token)
{
	t_command	*command;
	printf("handle redirect\n");
	if (token->type == PIPE)
		pipe_it(shell);
	else
	{
		command = (t_command *) ft_lstlast(shell->command_list)->content;
		if (token->type & (I_FILE | HERE_DOC))
			command->infile.type = token->type;
		if (token->type & (O_FILE | O_FILE_APPEND))
			command->outfile.type = token->type;
	}
	return (token->next);
}

bool	commander(t_shell *shell)
{
	t_token_stack	*token;

	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	token = shell->tokens;
	while (token)
	{
		token = get_first_token(token, 0x3fc);
		if (!token)
			break ;
		if (token->type & (O_FILE | O_FILE_APPEND | I_FILE | HERE_DOC | PIPE))
			token = handle_redirections(shell, token);
		printf("token %p %s\n", token, get_token_str_type(token->type));
		if ((token->type & (STR | QSTR | DQSTR)))
			token = expande(shell, token, (t_command *)
					ft_lstlast(shell->command_list)->content);
		token = token->next;
	}
	t_list *commands = shell->command_list;
	printf("%p\n", commands);
	while (commands) {
		t_list *argvs = ((t_command * ) commands->content)->argv_builder; 
		while (argvs) {
			printf("argv: %s\n", (char *)argvs->content);
			argvs = argvs->next;
		}
		commands = commands->next;
		printf("------\n");
	}
	ft_lstclear(&shell->command_list, (void (*)(void *))free_command);
	return (1);
}
