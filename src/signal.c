/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 02:34:13 by alrey             #+#    #+#             */
/*   Updated: 2025/08/26 02:34:13 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cmd_sigint(int signum)
{
	(void)signum;
	printf("\n");
}

void	main_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	main_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

// TODO maybe find a better way :x
// SIGPIPE fix: echo salut | < salut cat (causing SIGPIPE because the read end of the pipe is closed and replaced by de I_FILE) 
void	signals_main(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_DFL);
}

void	signals_cmd(void)
{
	signal(SIGINT, cmd_sigint);
	signal(SIGQUIT, cmd_sigint);
	signal(SIGPIPE, SIG_IGN);
}
