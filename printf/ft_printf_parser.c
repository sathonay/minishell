/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:15:33 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 21:06:49 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	extract_int(const char **str)
{
	int		val;

	val = 0;
	while (ft_isdigit(**str))
		val = val * 10 + *((*str)++) - '0';
	return (val);
}

void	extract_options(const char *format, t_options *opt)
{
	if (*format == '0' && format++)
		opt->adjustment_char = '0';
	if (*format == '#' && format++)
		opt->hex = 1;
	if (*format == ' ' && format++)
		opt->space = 1;
	if (*format == '+' && format++)
		opt->plus = 1;
	if (*format == '-' && format++)
		options_set_adjustment(opt, extract_int(&format), -1);
	if (ft_isdigit(*format))
		options_set_adjustment(opt, extract_int(&format), 1);
	if (*format == '.' && format++)
		options_set_precision(opt, extract_int(&format));
	opt->parse_end = format;
}

int	is_flag(const char *c)
{
	char	*flagset;

	flagset = "% c i d u s x X p ";
	while (*flagset)
	{
		if (ft_strncmp(c, flagset,
				lmin(ft_strchr(flagset, ' ') - flagset, 0)) == 0)
			return (1);
		flagset = ft_strchr(flagset, ' ') + 1;
	}
	return (0);
}

int	perform_flag(t_options *opt, const char *format, va_list va)
{
	int	count;

	count = 0;
	if (*format == '%')
		count += ft_putchar(1, '%');
	else if (*format == 'c')
		count += ft_print_char(va_arg(va, int), opt);
	else if (*format == 'i' || *format == 'd')
		count += ft_print_int(va_arg(va, int), opt);
	else if (*format == 'u')
		count += ft_print_uint(va_arg(va, unsigned int), opt);
	else if (*format == 's')
		count += ft_print_str(va_arg(va, char *), opt);
	else if (*format == 'x' && opt_set_flag(opt, 'x'))
		count += ft_print_hex(va_arg(va, unsigned int), opt);
	else if (*format == 'X' && opt_set_flag(opt, 'X'))
		count += ft_print_hex(va_arg(va, unsigned int), opt);
	else if (*format == 'p')
		count += ft_print_ptr(va_arg(va, unsigned long), opt);
	return (count);
}
