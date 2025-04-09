/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/16 23:25:03 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// f forward
static char	*strndupf(const char **s1, size_t length)
{
	const char	*end;
	char		*dup;

	end = *s1 + length;
	dup = malloc (sizeof(char) * length + 1);
	if (dup)
	{
		dup[length] = '\0';
		while (length--)
			dup[length] = (*s1)[length];
	}
	*s1 = end;
	return (dup);
}

// oe or end
static char	*strchroe(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return ((char *) s);
}

static void	free_split(char **tab)
{
	while (*tab)
		free(*(tab++));
	free(tab);
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
	char	**splits;
	char	**o_splits;

	splits = malloc (sizeof(char *) * (word_count(s, c) + 1));
	if (!splits)
		return (NULL);
	o_splits = splits;
	while (*s)
	{
		if (*s != c)
		{
			*(splits++) = strndupf(&s, strchroe(s, c) - s);
			if (!*(splits - 1))
				free_split(o_splits);
		}
		else
			s++;
	}
	*splits = NULL;
	return (o_splits);
}
