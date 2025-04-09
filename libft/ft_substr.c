/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/17 01:25:47 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	strlen;
	char	*sub;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (strlen < start)
		start = strlen;
	if (strlen - start < len)
		len = strlen - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	sub[len] = '\0';
	while (len--)
		sub[len] = s[start + len];
	return (sub);
}
