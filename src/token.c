/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:40 by alrey             #+#    #+#             */
/*   Updated: 2025/07/21 20:06:13 by alrey            ###   ########.fr       */
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

t_token_stack	*get_next_token(t_token_stack *token, enum e_token_type type)
{
	token = token;
	while (token && token->type != NONE)
	{
		if ((token->type & type) > 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}
