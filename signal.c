/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 02:34:13 by alrey             #+#    #+#             */
/*   Updated: 2025/09/10 18:58:30 by alrey            ###   ########.fr       */
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

void	signals_main(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_cmd(void)
{
	signal(SIGINT, cmd_sigint);
	signal(SIGQUIT, cmd_sigint);
}
