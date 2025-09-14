/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nt_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:26:15 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 18:17:41 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	nt_array_size(void **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}
