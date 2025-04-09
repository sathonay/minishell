/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/17 01:30:33 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	llen(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n / 10 > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	iabs(int i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

char	*ft_itoa(int n)
{
	size_t	strlen;
	char	*str;

	strlen = llen(n);
	if (n < 0)
		strlen++;
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	str[strlen] = '\0';
	if (n < 0)
		str[0] = '-';
	while (n / 10 != 0)
	{
		str[--strlen] = '0' + iabs(n % 10);
		n /= 10;
	}
	str[--strlen] = '0' + iabs(n % 10);
	return (str);
}
