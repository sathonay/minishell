/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:00:09 by alrey             #+#    #+#             */
/*   Updated: 2025/08/22 19:38:46 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token_stack	*lexing(t_token_stack *token)
{
	t_token_stack	*valid;

	valid = token;
	while (valid)
	{
		valid = get_first_token(valid, 0x3fc);
		if (valid && valid->type == PIPE)
		{
			token = get_first_token(valid->next, 0x3fc);
			if (!token || (token->type & (STR | DQSTR | QSTR)) == 0)
				return (valid);
			valid = token;
		}
		if (valid && (valid->type & (O_FILE | I_FILE | O_FILE_APPEND | HERE_DOC
					| PIPE)) > 0)
		{
			token = get_first_token(valid->next, 0x3fc ^ valid->type);
			if (!token || (token->type & (STR | DQSTR | QSTR)) == 0)
				return (valid);
			valid = token;
		}
		if (valid)
			valid = valid->next;
	}
	return (NULL);
}

bool	lexer(t_token_stack *token)
{
	token = lexing(token);
	if (token)
		printf("mini@: lex error near %s\n", token->start);
	return (!token);
}
