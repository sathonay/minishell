/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:01 by alrey             #+#    #+#             */
/*   Updated: 2024/11/09 17:06:18 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*l_occ;

	l_occ = NULL;
	while (*s)
	{
		if (*s == (unsigned char) c)
			l_occ = (char *) s;
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return (l_occ);
}
