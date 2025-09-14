/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:45:33 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 21:06:40 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**str_split_first(char *str, char sep)
{
	char	*match_ptr;
	char	**split;

	match_ptr = str;
	split = ft_calloc(2 + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (*match_ptr && *match_ptr != sep)
		match_ptr++;
	if (!*match_ptr)
		split[0] = ft_strdup(str);
	else
	{
		split[0] = ft_substr(str, 0, match_ptr - str);
		split[1] = ft_strdup(match_ptr + 1);
	}
	return (split);
}

char	*str_concat_consume(char *str1, char *str2, int str_to_consome)
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
