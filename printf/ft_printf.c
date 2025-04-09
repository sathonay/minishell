/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:08:24 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 20:14:30 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_chrstr(int c, char *charset)
{
	if (!charset)
		return (0);
	while (*charset)
	{
		if ((unsigned char) c == (unsigned char) *charset)
			return (1);
		else
			charset++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	va_list		va;
	t_options	opt;

	count = 0;
	va_start(va, format);
	while (*format)
	{
		if (*format == '%')
		{
			apply_default_options(&opt);
			extract_options(format + 1, &opt);
			if (is_flag(opt.parse_end))
			{
				count += perform_flag(&opt, opt.parse_end, va);
				format = opt.parse_end + 1;
				continue ;
			}
		}
		count += write(1, format++, 1);
	}
	return (count);
}
