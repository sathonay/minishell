/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:58:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/09 17:15:48 by alrey            ###   ########.fr       */
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

static int	is_str_int(char *str)
{
	char	c;
	int		i;

	c = '+';
	i = 0;
	if (*str == '+' || *str == '-')
		c = *(str++);
	while (*str && *str == '0')
		str++;
	while (ft_isdigit(str[i]) && i < 10)
		i++;
	return (str[i] == '\0'
		&& (i < 10
			|| (((!c || c == '+') && ft_strcmp(str, "2147483647") <= 0)
				|| ((c == '-' && ft_strcmp(str, "2147483648") <= 0)))));
}

int	ft_exit(t_shell *shell, t_command command)
{
	(void) command;
	int exit_code;

	if ((command.argv[1] && !is_str_int(command.argv[1]))
		|| nt_array_size((void **) command.argv) > 2)
	{
		printf("usage:\n\texit [exit_code]");
		return (1);
	}
	exit_code = 0;
	if (command.argv[1])
		exit_code = ft_atoi(command.argv[1]);
	printf("exiting\n");
	free_shell(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}
