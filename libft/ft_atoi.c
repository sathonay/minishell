/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/06 23:07:40 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

int	ft_atoi(const char *str)
{
	char	sign;
	int		val;

	sign = 1;
	val = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (ft_isdigit(*str))
		val = val * 10 + *(str++) - '0';
	return (sign * val);
}
