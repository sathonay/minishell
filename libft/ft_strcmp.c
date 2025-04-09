/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:24:42 by alrey             #+#    #+#             */
/*   Updated: 2025/01/02 17:24:07 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((unsigned char) *s1 && (unsigned char) *s2
		&& (unsigned char) *s1 == (unsigned char) *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
