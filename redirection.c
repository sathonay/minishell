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

void	here_is_the_doc(t_command *command)
{
	t_redirect	*infile;
	char		*line;

	infile = &command->infile;
	line = NULL;
	if (infile->type == HERE_DOC && infile->path)
	{
		infile->fd = open(infile->path, O_CREAT | O_RDWR | O_TRUNC, 0777);
		line = readline("");
		while (line)
		{
			if (!line
				|| ft_strncmp(line, infile->eof, ft_strlen(infile->eof)) == 0)
				break ;
			write(infile->fd, line, ft_strlen(line));
			write(infile->fd, "\n", 1);
			(free_str(&line), line = readline(""));
		}
		(free_str(&line), close(infile->fd));
		infile->fd = open(infile->path, O_CREAT | O_RDONLY, 0777);
	}
}

void	apply_redirection(t_command command)
{
	if (command.prev_pipe[1] > 0)
		close(command.prev_pipe[1]);
	if (command.next_pipe[0] > 0)
		close(command.next_pipe[0]);
	if (command.infile.fd > 0)
		dup2_close_old(command.infile.fd, 0);
	else if (command.prev_pipe[0] > 0)
		dup2_close_old(command.prev_pipe[0], 0);
	if (command.outfile.fd > 0)
		dup2_close_old(command.outfile.fd, 1);
	else if (command.next_pipe[1] > 0)
		dup2_close_old(command.next_pipe[1], 1);
}
