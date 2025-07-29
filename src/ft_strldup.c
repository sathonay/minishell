/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 03:55:42 by alrey             #+#    #+#             */
/*   Updated: 2025/07/29 19:45:38 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strldup(const char *s1, size_t len)
{
	char	*dup;

	dup = ft_calloc(len + 1, sizeof(char));
	if (dup)
		ft_strlcpy(dup, s1, len + 1);
	return (dup);
}
