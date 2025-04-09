/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:30 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:42:43 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uint(unsigned int n, t_options *opt)
{
	int	size;
	int	count;

	if (!opt)
		return (ft_putunbr(1, n));
	size = uintlen(n) * (!opt || n != 0 || opt->precision != 0);
	count = 0;
	while (opt->direction > 0 && lmin(opt->precision, size) < opt->adjustment--)
		count += write(1, &(opt->adjustment_char), 1);
	while (opt->precision > 0 && size < opt->precision--)
		count += write(1, "0", 1);
	if (size)
		count += ft_putunbr(1, n);
	count += ft_print_right_padding(count, opt);
	return (count);
}

static int	print_int_sign(int n, t_options *opt)
{
	if (0 <= n && opt && opt->plus)
		return (ft_putchar(1, '+'));
	else if (n < 0)
		return (ft_putchar(1, '-'));
	return (0);
}

static unsigned int	ft_itoui(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

int	ft_print_int(int n, t_options *opt)
{
	int	size;
	int	count;

	count = 0;
	if (!opt)
		return (print_int_sign(n, NULL) + ft_putunbr(1, ft_itoui(n)));
	size = intlen(n) * (n != 0 || opt->precision != 0);
	if (opt->space && !(opt->plus) && n >= 0)
		count += ft_putchar(1, ' ');
	if (opt->adjustment_char == '0')
		count += print_int_sign(n, opt);
	count += ft_print_left_padding(lmin(opt->precision, size) + count
			+ (opt->adjustment_char == ' '
				* (n < 0 || (0 <= n && opt && opt->plus))), opt);
	if (opt->adjustment_char == ' ')
		count += print_int_sign(n, opt);
	count += ft_print_precision(size, opt);
	if (size)
		count += ft_putunbr(1, ft_itoui(n));
	count += ft_print_right_padding(count, opt);
	return (count);
}
