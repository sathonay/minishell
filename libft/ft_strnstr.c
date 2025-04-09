/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/11 12:51:58 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*needle_o;

	if (!*needle)
		return ((char *) haystack);
	needle_o = needle;
	while (len && *haystack)
	{
		while (len-- && *haystack && *needle
			&& haystack[needle - needle_o] == *needle)
			needle++;
		if (!*needle)
			return ((char *) haystack);
		len += (needle - needle_o);
		needle = needle_o;
		haystack++;
	}
	return (NULL);
}
