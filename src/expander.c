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
	else if (str_to_consome == 0)
		free_str(&str1);
	return (concat);
}

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

static void	**ft_list_to_array(t_list *list)
{
	void	**array;
	size_t	i;

	if (!list)
		return (NULL);
	array = ft_calloc(ft_lstsize(list) + 1, sizeof(void *));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		array[i] = list->content;
		list = list->next;
		i++;
	}
	return (array);
}

t_expander_result	expande(t_shell *shell, t_token_stack *token)
{
	t_expander_result	res;

	res.str = NULL;
	res.end = token;
	(void) ft_list_to_array(NULL);
	if (res.end && (res.end->type & (STR | QSTR | DQSTR)))
	{
		res.str = expand_env_var(shell, res.end);
		while (res.end->next && (res.end->next->type & (STR | QSTR | DQSTR)))
		{
			if (!res.str)
				return (res);
			res.str = ft_strjoin(res.str, expand_env_var(shell, res.end->next));
			if ((res.end->next->type & (STR | QSTR | DQSTR)) == 0)
				break ;
			res.end = res.end->next;
		}
		return (res);
	}
	return (res);
}
