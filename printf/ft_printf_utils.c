/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:24:24 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:14:42 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str)
		while (str[len])
			len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (--n && (unsigned char) *s1 && (unsigned char) *s2
		&& (unsigned char) *s1 == (unsigned char) *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return (NULL);
}
