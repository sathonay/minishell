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

static t_token_stack	*handle_redirections(t_token_stack *token)
{

	if (token )

	return (token);
}

bool	commander(t_shell *shell)
{
	t_token_stack	*token;

	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	token = shell->tokens;
	while (token)
	{
		token = get_first_token(token, STR | QSTR | DQSTR | PIPE);
		if (!token)
			break ;
		if (token->type == PIPE)
			ft_lstadd_back(&shell->command_list,
				ft_lstnew(ft_calloc(sizeof(t_command), 1)));
		if (token->type & (O_FILE | O_FILE | I_FILE | HERE_DOC))
			// TODO handle redirect
		printf("token %p %s\n", token, token->start);
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
	}
	ft_lstclear(&shell->command_list, (void (*)(void *))free_command);
	return (1);
}
