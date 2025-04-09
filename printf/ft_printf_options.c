/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:38:49 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 21:02:11 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_default_options(t_options *opt)
{
	opt->precision = -1;
	opt->plus = 0;
	opt->space = 0;
	opt->adjustment = 0;
	opt->direction = 0;
	opt->adjustment_char = ' ';
	opt->flag = 0;
	opt->size = 0;
	opt->hex = 0;
}

void	options_set_precision(t_options *opt, int precision)
{
	opt->precision = precision;
	opt->adjustment_char = ' ';
}

void	options_set_adjustment(t_options *opt, int adjust, int dir)
{
	if (!opt)
		return ;
	opt->adjustment = adjust;
	opt->direction = dir;
}

t_options	*opt_set_flag(t_options *opt, char flag)
{
	if (opt)
	{
		opt->flag = flag;
	}
	return (opt);
}
