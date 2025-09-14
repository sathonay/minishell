/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:40 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 21:12:47 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	append_token(t_shell *shell, t_token_stack *token)
{
	t_token_stack	*head;

	if (!token)
		return (0);
	token->next = NULL;
	head = shell->tokens;
	if (!head)
	{
		shell->tokens = token;
		return (1);
	}
	while (head->next)
		head = head->next;
	head->next = token;
	return (1);
}

t_token_stack	*get_first_token(t_token_stack *token, t_token_type type)
{
	while (token && (token->type & type) == 0)
		token = token->next;
	return (token);
}

char	*get_token_str_type(t_token_type type)
{
	if (type == NONE)
		return ("NONE");
	if (type == EMPTY)
		return ("EMPTY");
	if (type == STR)
		return ("STR");
	if (type == QSTR)
		return ("QSTR");
	if (type == DQSTR)
		return ("DQSTR");
	if (type == PIPE)
		return ("PIPE");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == I_FILE)
		return ("I_FILE");
	if (type == O_FILE)
		return ("O_FILE");
	if (type == O_FILE_APPEND)
		return ("O_FILE_APPEND");
	return (NULL);
}

void	print_token_stack(t_shell *shell)
{
	t_token_stack	*token;

	token = shell->tokens;
	while (token)
	{
		printf("pointer %p\n", token);
		printf("type %s\n", get_token_str_type(token->type));
		printf("size %ld\n", token->end - token->start);
		printf("content: ");
		write(1, token->start, token->end - token->start);
		write(1, "\n", 1);
		printf("next %p\n\n", token->next);
		token = token->next;
	}
}
