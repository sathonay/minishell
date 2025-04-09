/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:58:18 by alrey             #+#    #+#             */
/*   Updated: 2025/03/25 17:10:56 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strconcat(char *s1, char const *s2)
{
	char	*concat;

	concat = ft_strjoin(s1, s2);
	if (!concat)
		return (s1);
	if (s1)
		free(s1);
	return (concat);
}
