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

static char	*str_concat_consume(char *str1, char *str2, int str_to_consome)
{
	char	*concat;
	
	concat = ft_strjoin(str1, str2);
	if (str_to_consome == 2)
	{
		free_str(&str2);
		free_str(&str1);
	}
	else if (str_to_consome == 1)
		free_str(&str2);
	else if (str_concat_consume == 0)
		free_str(&str1);
	return (concat);
} 

static char	*expand_env_var(t_shell *shell, t_token_stack *token)
{
	char	*token_str;
	size_t	l;
	char	*str;

	str = NULL;
	token_str = token->start;
	while (token_str < token->end)
	{
		if (*token_str == '$') {
			token_str++;
			l = 0;
			while (ft_isalnum(token_str[l]) || token_str[l] == '_')
				l++;
			
			printf("env: %s\n", ft_get_env(shell, token_str, l));
			str = str_concat_consume(str, ft_get_env(shell, token_str, l), 2);
			token_str += l;
		}
		else
			str = str_concat_consume(str, ft_substr(token_str, 0, 1), 2);
		token_str++;
	}
	printf("expand_var_res: %s\n", str);
	return (str);
}

void	expander(t_shell *shell)
{
	t_token_stack	*token;
	t_list			*argv;
	char			*str;

	str = NULL;
	token = shell->tokens;
	if (!token)
		return ;
	while (token)
	{
		token = get_first_token(token, STR | QSTR | DQSTR);
		if (!token)
			return ;
		str = expand_env_var(shell, token);
		while (token->next && (token->next->type & (STR | QSTR | DQSTR)) > 0)
		{
			str = ft_strjoin(str, expand_env_var(shell, token->next));
			token = token->next;
		}
		printf("linked str: %s\n", str);
		token = token->next;
	}
}

