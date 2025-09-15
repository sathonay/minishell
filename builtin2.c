/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:58:55 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 15:02:44 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_cd(t_shell *shell, t_command command)
{
	char	*path;

	if (nt_array_size((void **) command.argv) > 2)
		return (printf("usage:\n\tcd PATH\n"), 1);
	if (nt_array_size((void **) command.argv) == 1)
	{
		path = ft_get_env(shell, "HOME", 4);
		if (!path)
			return (printf("el minishello: cd : HOME not set"), 1);
	}
	if (nt_array_size((void **) command.argv) == 2)
		path = command.argv[1];
	if (nt_array_size((void **) command.argv) == 2
		&& ft_strcmp(path, "-") == 0)
	{
		path = ft_get_env(shell, "OLDPWD", 6);
		if (!path)
			return (printf("el minishello: cd : OLDPWD not set"), 1);
	}
	if (ft_chdir(shell, path))
		printf("cd: %s: %s\n", strerror(errno), command.argv[1]);
	return (0);
}

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
			|| (((c == '+') && ft_strcmp(str, "2147483647") <= 0)
				|| ((c == '-' && ft_strcmp(str, "2147483648") <= 0)))));
}

int	ft_exit(t_shell *shell, t_command command)
{
	int	exit_code;

	(void) command;
	if (nt_array_size((void **) command.argv) > 2)
	{
		printf("usage:\n\texit [exit_code]\n");
		return (1);
	}
	if (command.prev_pipe[0] > 0 || command.next_pipe[1] > 0)
		return (0);
	exit_code = 0;
	if (command.argv[1] && !is_str_int(command.argv[1]))
		exit_code = 2;
	if (command.argv[1] && is_str_int(command.argv[1]))
		exit_code = ft_atoi(command.argv[1]);
	write(2, "exiting\n", ft_strlen("exiting\n"));
	free_shell(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}
