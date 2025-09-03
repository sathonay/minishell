/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:50 by alrey             #+#    #+#             */
/*   Updated: 2025/09/03 06:02:28 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_env(t_shell *shell, t_command command)
{
	char	**env;

	(void) command;
	env = shell->env;
	if (!env)
		return (0);
	while (*env)
		printf("%s\n", *(env++));
	return (0);
}

int	ft_export(t_shell *shell, t_command command)
{
	int		bad_format;
	char	**split;

	split = split_first(command.argv[1], '=');
	bad_format = split[0] && !split[1];
	if (!bad_format)
	{
		split[0] = str_concat_consume(split[0], "=", 0);
		env_set(shell, split[0], split[1]);
	}
	free_str_array(split);
	return (bad_format);
}

int	ft_unset(t_shell *shell, t_command command)
{
	env_unset(shell, command.argv[1]);
	return (9);
}

int	ft_pwd(t_shell *shell, t_command command)
{
	char	*path;

	(void) shell;
	(void) command;
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	ft_cd(t_shell *shell, t_command command)
{
	(void) shell;
	if (chdir(command.argv[1]))
		printf("cd: %s: %s\n", strerror(errno), command.argv[1]);
	return (0);
}
