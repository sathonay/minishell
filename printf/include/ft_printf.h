/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:47:25 by alrey             #+#    #+#             */
/*   Updated: 2024/12/23 21:07:03 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>

int			ft_isdigit(int c);

size_t		ft_strlen(const char *str);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strchr(const char *s, int c);

size_t		ulonglen_base(unsigned long ul, int base);

size_t		uintlen(unsigned int ui);

size_t		intlen(int i);

long		lmin(long value, long min);

typedef struct s_options
{
	int			precision;
	int			plus;
	int			space;
	int			adjustment;
	int			direction;
	int			size;
	int			hex;
	char		adjustment_char;
	char		flag;
	const char	*parse_end;
}			t_options;

int			ft_putnchar(int fd, int n, char c);

int			ft_putchar(int fd, int c);

int			ft_putunbr_base(int fd, unsigned long nbr,
				const char *base, int base_l);

int			ft_putunbr(int fd, unsigned long n);

void		apply_default_options(t_options *opt);

void		options_set_adjustment(t_options *opt, int adjust, int dir);

void		options_set_precision(t_options *opt, int precision);

t_options	*opt_set_flag(t_options *opt, char flag);

int			ft_printf(const char *format, ...);

int			ft_print_precision(int size, t_options *opt);

int			ft_print_left_padding(int size, t_options *opt);

int			ft_print_right_padding(int size, t_options *opt);

int			ft_print_char(int c, t_options *opt);

int			ft_print_str(const char *str, t_options *opt);

int			ft_print_uint(unsigned int n, t_options *opt);

int			ft_print_int(int n, t_options *opt);

int			ft_print_hex(unsigned long nbr, t_options *opt);

int			ft_print_ptr(unsigned long nbr, t_options *opt);

int			extract_int(const char **str);

void		extract_options(const char *format, t_options *opt);

int			is_flag(const char *c);

int			perform_flag(t_options *opt, const char *format, va_list va);

#endif
