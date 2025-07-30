/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:40 by alrey             #+#    #+#             */
/*   Updated: 2025/07/30 06:20:22 by alrey            ###   ########.fr       */
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

t_token_stack	*get_first_token(t_token_stack *token, t_token_type type)
{
	while (token && (token->type & type) == 0)
		token = token->next;
	return (token);
}
char *get_token_str_type(t_token_type type)
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