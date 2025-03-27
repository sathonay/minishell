/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2025/03/20 19:06:54 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_split(char **tab)
{
	while (*tab)
		free(*(tab++));
	free(tab);
	return (NULL);
}

static size_t	word_count(char const *s, char c)
{
	size_t	strs;
	size_t	i;

	strs = 0;
	i = 0;
	while (s[i])
		if (s[i++] != c && (!s[i] || s[i] == c))
			strs++;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char		**splits;
	char		**o_splits;
	const char	*lvc;

	splits = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (!splits)
		return (NULL);
	o_splits = splits;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (o_splits);
		lvc = s;
		while (*s && *s != c)
			s++;
		*(splits++) = ft_substr(lvc, 0, s - lvc);
		if (!*(splits - 1))
			return (free_split(o_splits));
	}
	return (o_splits);
}
