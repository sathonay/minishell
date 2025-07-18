/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:40 by alrey             #+#    #+#             */
/*   Updated: 2025/07/15 13:05:50 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void append_token(t_shell *shell, t_token_stack *token)
{
	t_token_stack **head = &shell->tokens;
	while (*head)
		head = &(*head)->next;
	*head = token;
}

to_token_stack	*get_next_token(to_token_stack *token, e_token_type type)
{
	token = token->next;
	while (token && token->type != NONE)
	{
		if (token->type & type > 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void free_token_stack(t_shell *shell)
{
	t_token_stack *token;

	if (shell->tokens)
	{
		while (shell->tokens)
		{
			token = shell->tokens;
			shell->tokens = token->next;
			free(token);
		}
		shell->tokens = NULL;	
	}
}
