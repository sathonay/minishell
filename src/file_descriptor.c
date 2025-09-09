/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 05:38:00 by alrey             #+#    #+#             */
/*   Updated: 2025/09/09 16:34:58 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	dup_in_and_out(int fd[2])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

int	dup2_close_old(int old, int new)
{
	int	ret;

	if (old == -1)
		return (-1);
	ret = dup2(old, new);
	if (ret == -1)
		return (-1);
	if (old != new)
		close(old);
	return (ret);
}
