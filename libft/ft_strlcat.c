/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:01 by alrey             #+#    #+#             */
/*   Updated: 2024/11/17 00:15:12 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	if (!dstsize || i >= dstsize)
		return (dstsize + ft_strlen(src));
	j = 0;
	while (*(src + j) && i + j < dstsize - 1)
		*(dst++ + i) = *(src + j++);
	*(dst + i) = '\0';
	return (i + j + ft_strlen(src + j));
}
