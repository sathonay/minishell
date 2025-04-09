/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:21:26 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 16:09:31 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex_type(t_options *opt)
{
	int	count;

	count = 0;
	if (opt->hex)
		count += write(1, "0", 1);
	if (opt->hex && opt->hex--)
		count += write(1, &(opt->flag), 1);
	return (count);
}

static int	perform_left_adjustment(int size, t_options *opt)
{
	int	count;

	if (!opt)
		return (0);
	if (!size)
		return (ft_print_left_padding(1, opt));
	count = 0;
	if (opt->adjustment_char == '0')
		count += print_hex_type(opt);
	count += ft_print_left_padding(lmin(size, 1), opt);
	if (opt->adjustment_char == ' ')
		count += print_hex_type(opt);
	return (count);
}

static int	ft_puthex(unsigned long nbr, const char *hex)
{
	int	count;

	count = 0;
	if (nbr > 15)
		count += ft_puthex(nbr / 16, hex);
	count += ft_putchar(1, *(hex + (nbr % 16)));
	return (count);
}

int	ft_print_hex(unsigned long nbr, t_options *opt)
{
	int			size;
	int			count;
	char		*hex;

	if (!opt)
		return (ft_puthex(nbr, "0123456789ABCDEF"));
	if (nbr == 0 && opt->precision == 0)
		return (ft_print_left_padding(0, opt)
			+ ft_print_right_padding(0, opt));
	size = ulonglen_base(nbr, 16);
	count = 0;
	if (opt->flag == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	count += perform_left_adjustment((lmin(opt->precision, size)
				+ ((opt->hex > 0) * 2)) * (nbr > 0), opt);
	count += ft_print_precision(size, opt);
	if (size > 0)
		count += ft_puthex(nbr, hex);
	count += ft_print_right_padding(count, opt);
	return (count);
}
