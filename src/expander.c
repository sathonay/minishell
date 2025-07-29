/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:17:27 by alrey             #+#    #+#             */
/*   Updated: 2025/07/29 19:17:27 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expander(t_shell *shell)
{
	t_token_stack	*token;
	char			*str;
	char			*str2;

	token = shell->tokens;
	if (!token)
		return ;
	while (token)
	{
		token = get_first_token(token, STR | QSTR | DQSTR);
		printf("token type: %s\n", get_token_str_type(token->type));

		str = ft_strldup(token->start, token->end - token->start);

		while (token->next && (token->next->type & (STR | QSTR | DQSTR)) > 0)
		{
			str2 = ft_strldup(token->next->start,
				token->next->end - token->next->start);
			str = ft_strjoin(str, str2);
			free(str2);
			token = token->next;
		}
		printf("linked str: %s\n", str);
		token = token->next;
	}
}

