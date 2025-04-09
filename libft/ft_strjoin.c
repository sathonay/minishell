/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:01 by alrey             #+#    #+#             */
/*   Updated: 2024/11/16 23:25:36 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_l;
	size_t	s2_l;
	char	*join;

	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (join == NULL)
		return (NULL);
	join[s1_l + s2_l] = '\0';
	while (s2_l--)
		join[s1_l + s2_l] = s2[s2_l];
	while (s1_l--)
		join[s1_l] = s1[s1_l];
	return (join);
}
