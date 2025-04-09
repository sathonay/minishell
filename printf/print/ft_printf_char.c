/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:20:04 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:43:38 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c, t_options *opt)
{
	int	count;

	count = 0;
	while (opt && opt->direction > 0 && opt->adjustment-- > 1)
		count += write(1, &(opt->adjustment_char), 1);
	count += write(1, &c, 1);
	count += ft_print_right_padding(count, opt);
	return (count);
}
