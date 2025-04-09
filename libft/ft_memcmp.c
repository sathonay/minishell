/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:01 by alrey             #+#    #+#             */
/*   Updated: 2024/11/06 23:07:41 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	ss1 = s1;
	ss2 = s2;
	while (n--)
	{
		if (*ss1 == *ss2)
		{
			ss1++;
			ss2++;
		}
		else
			return (*ss1 - *ss2);
	}
	return (0);
}
