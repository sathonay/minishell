/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:00 by alrey             #+#    #+#             */
/*   Updated: 2024/11/17 01:38:56 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_incharset(char c, char const *charset)
{
	if (!charset)
		return (0);
	while (*charset)
	{
		if (c == *charset)
			return (1);
		else
			charset++;
	}
	return (0);
}

/*
while (*trim)
{
	if (!ft_is_incharset(*trim, set))
		rtp = trim + 1;
	trim++;
}
*/	
// ltp -> left_trim_position
// rtp -> right_trim_postition
char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*ltp;
	char const	*rtp;
	char		*trim;

	if (!s1)
		return (NULL);
	ltp = s1;
	while (*ltp && ft_is_incharset(*ltp, set))
		ltp++;
	trim = (char *) ltp;
	rtp = ltp;
	while (*trim)
		if (!ft_is_incharset(*(trim++), set))
			rtp = trim;
	trim = malloc(sizeof(char) * (rtp - ltp + 1));
	if (trim == NULL)
		return (NULL);
	trim[rtp - ltp] = '\0';
	while (ltp < rtp--)
		trim[rtp - ltp] = *rtp;
	return (trim);
}
