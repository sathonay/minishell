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

static char	*str_concat_consume(char *str1, char *str2, bool str_to_consome)
{
	char	*concat;
	
	concat = ft_strjoin(str1, str2);
	if (str_to_consome)
		free(str2);
	else
		free(str1);
	return (concat);
} 

static char	*expand_env_var(t_token_stack *token)
{
	char	*token_str;
	size_t	l;
	char	*str;

	str = ft_calloc(1, sizeof(char));
	token_str = token->start;
	while (token_str < token->end)
	{
		if (*token_str == '$') {
			token++;
			l = 0;
			while (ft_isalnum(token_str[l]) && token_str[l] == '_')
				l++;
			//TODO concat env var str = str_concat_consume(str, ft_strldup(token_str, 1));
			token_str += l;
		}
		else
			str = str_concat_consume(str, ft_substr(token_str, 0, 1), 1);
		token_str++;
	}
	printf("expand_var_res: %s\n", str);
	return (str);
}

void	expander(t_shell *shell)
{
	t_token_stack	*token;
	char			*str;

	token = shell->tokens;
	if (!token)
		return ;
	while (token)
	{
		token = get_first_token(token, STR | QSTR | DQSTR);
		printf("token type: %s\n", get_token_str_type(token->type));
		str = expand_env_var(token);
		while (token->next && (token->next->type & (STR | QSTR | DQSTR)) > 0)
		{
			str = ft_strjoin(str, expand_env_var(token->next));
			token = token->next;
		}
		printf("linked str: %s\n", str);
		token = token->next;
	}
}

