/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:20:04 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 15:13:57 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_precision(int size, t_options *opt)
{
	if (opt && opt->precision > size)
		return (ft_putnchar(1, opt->precision - size, '0'));
	return (0);
}

int	ft_print_left_padding(int size, t_options *opt)
{
	if (opt && opt->direction > 0 && opt->adjustment > size)
		return (ft_putnchar(1, opt->adjustment - size, opt->adjustment_char));
	return (0);
}

int	ft_print_right_padding(int size, t_options *opt)
{
	if (opt && opt->direction < 0 && opt->adjustment > size)
		return (ft_putnchar(1, opt->adjustment - size, ' '));
	return (0);
}
