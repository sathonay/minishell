/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:18:50 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:34:43 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ulonglen_base(unsigned long ul, int base)
{
	size_t	len;

	len = 1;
	while (ul / base)
	{
		ul /= base;
		len++;
	}
	return (len);
}

size_t	uintlen(unsigned int ui)
{
	return (ulonglen_base(ui, 10));
}

size_t	intlen(int i)
{
	if (i < 0)
		return (uintlen(-i));
	return (uintlen(i));
}
