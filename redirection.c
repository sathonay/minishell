/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:36:15 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 17:36:15 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	apply_redirection(t_command command)
{
	dup2_close_old(command.pipe[0], 0);
	dup2_close_old(command.infile.fd, 0);
	dup2_close_old(command.pipe[1], 1);
	dup2_close_old(command.outfile.fd, 1);
}
