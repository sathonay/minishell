/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:45:27 by alrey             #+#    #+#             */
/*   Updated: 2025/08/26 18:01:37 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;	
	}
}

void	free_str_array(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs && strs[i])
		free(strs[i++]);
	if (strs)
		free(strs);
	strs = NULL;
}
