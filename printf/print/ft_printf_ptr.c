/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:22:17 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:43:15 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long nbr, t_options *opt)
{
	t_options	sopt;

	if (!nbr)
		return (ft_print_str("(nil)", opt));
	if (!opt)
	{
		opt = &sopt;
		apply_default_options(opt);
	}
	opt->hex = 1;
	opt->flag = 'x';
	return (ft_print_hex(nbr, opt));
}
