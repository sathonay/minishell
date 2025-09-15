/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:17:27 by alrey             #+#    #+#             */
/*   Updated: 2025/09/03 06:03:08 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*expand_env_var(t_shell *shell, t_token_stack *token)
{
	char	*t_str;
	size_t	l;
	char	*str;

	if (token->type == QSTR)
		return (ft_substr(token->start, 0, token->end - token->start));
	str = NULL;
	t_str = token->start;
	while (t_str < token->end)
	{
		if (*t_str == '$')
		{
			t_str++;
			l = 0;
			while (ft_isalnum(t_str[l]) || t_str[l] == '_')
				l++;
			if (*t_str == '?')
				l++;
			str = str_concat_consume(str, ft_get_env(shell, t_str, l), 2);
			t_str += l;
			continue ;
		}
		str = str_concat_consume(str, ft_substr(t_str++, 0, 1), 2);
	}
	return (str);
}

t_expander_result	expande(t_shell *shell, t_token_stack *token)
{
	t_expander_result	res;

	res.str = NULL;
	res.end = token;
	if (res.end && (res.end->type & (STRINGS)))
	{
		res.str = expand_env_var(shell, res.end);
		while (res.end->next && (res.end->next->type & (STRINGS)))
		{
			if (!res.str)
				return (res);
			res.str = str_concat_consume(res.str,
					expand_env_var(shell, res.end->next), 2);
			if ((res.end->next->type & (STRINGS)) == 0)
				break ;
			res.end = res.end->next;
		}
		return (res);
	}
	return (res);
}
