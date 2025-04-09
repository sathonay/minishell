/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:31:00 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 14:43:23 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(const char *str, t_options *opt)
{
	int	size;
	int	count;

	if (!str)
		str = "(null)";
	size = ft_strlen(str);
	if (!opt)
		write(1, str, size);
	if (opt->precision >= 0 && size > opt->precision)
		size = opt->precision;
	count = size;
	if (opt->direction > 0 && opt->adjustment > size)
		count += ft_putnchar(1, opt->adjustment - size, ' ');
	write(1, str, size);
	count += ft_print_right_padding(count, opt);
	return (count);
}
