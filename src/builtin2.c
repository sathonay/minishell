/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:58:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/03 06:00:47 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_echo(t_shell *shell, t_command command)
{
	bool	print_newline;

	(void) shell;
	command.argv++;
	print_newline = true;
	while (*command.argv && ft_strncmp(*command.argv, "-n", 2) == 0)
	{
		command.argv++;
		print_newline = false;
	}
	while (*command.argv)
	{
		printf("%s", *command.argv);
		command.argv++;
		if (*command.argv)
			printf(" ");
	}
	if (print_newline)
		printf("\n");
	return (0);
}

int	ft_exit(t_shell *shell, t_command command)
{
	(void) command;
	printf("exiting\n");
	free_shell(shell);
	rl_clear_history();
	exit(0);
	return (0);
}
