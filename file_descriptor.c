/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 05:38:00 by alrey             #+#    #+#             */
/*   Updated: 2025/09/17 08:12:27 by alrey            ###   ########.fr       */
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

	if (old <= 0)
		return (-1);
	ret = dup2(old, new);
	if (ret == -1)
		return (-1);
	if (old != new)
		close(old);
	return (ret);
}

void	close_fd(int *fd)
{
	if (*fd > 0)
		close(*fd);
	*fd = 0;
}

void	close_pipe(int pips[2], int wclose)
{
	if (wclose == 2)
	{
		dprintf(2, "closing pipes %d %d\n", pips[0], pips[1]);
		if (pips[0] > 0)
			close(pips[0]);
		if (pips[1] > 0)
			close(pips[1]);
	}
	if (wclose == 1 && pips[0] > 0)
		close(pips[1]);
	if (wclose == 0 && pips[1] > 0)
		close(pips[0]);
}
