/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/16 23:29:04 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (((((long) count) < 0) || (((long) size) < 0)) && (count && size))
		return (NULL);
	size *= count;
	ptr = malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	while (size--)
		ptr[size] = '\0';
	return (ptr);
}
