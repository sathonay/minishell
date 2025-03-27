/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:59:51 by alrey             #+#    #+#             */
/*   Updated: 2025/03/25 14:14:13 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char *str1, char *str2)
{
	size_t	str1l;
	size_t	str2l;
	char	*concat;

	str1l = ft_strlen(str1);
	str2l = ft_strlen(str2);
	concat = malloc(str1l + str2l);
	concat[str1l + str2l] = '\0';
	while (str2l-- > 0)
		concat[str1l + str2l] = str2[str2l];
	while (str1l-- > 0)
		concat[str1l] = str1[str1l];
	return (concat);
}
