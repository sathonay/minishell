/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:31:46 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:44:33 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar(int fd, int n, char c)
{
	int	count;

	count = 0;
	while (n--)
		count += write(fd, &c, 1);
	return (count);
}

int	ft_putunbr_base(int fd, unsigned long nbr, const char *base, int base_l)
{
	int	count;

	count = 0;
	if (nbr / base_l)
		count += ft_putunbr_base(fd, nbr / base_l, base, base_l);
	count += ft_putchar(fd, *(base + (nbr % base_l)));
	return (count);
}

int	ft_putunbr(int fd, unsigned long n)
{
	return (ft_putunbr_base(fd, n, "0123456789", 10));
}

int	ft_putchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}
