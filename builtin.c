/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:50 by alrey             #+#    #+#             */
/*   Updated: 2025/09/14 21:21:33 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	*find_builtin(t_shell *shell, const char *cmd_name)
{
	(void) shell;
	if (cmd_name == NULL)
		return (NULL);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset);
	return (NULL);
}

int	ft_env(t_shell *shell, t_command command)
{
	char	**env;

	if (nt_array_size((void **) command.argv) > 1)
	{
		printf("usage:\n\tenv\n");
		return (1);
	}
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

	if (nt_array_size((void **) command.argv) < 2)
		return (0);
	while (command.argv[1])
	{
		split = str_split_first(command.argv[1], '=');
		bad_format = split[0] && !split[1];
		if (!bad_format)
			env_set(shell, split[0], split[1]);
		free_str_array(split);
		command.argv++;
	}
	return (0);
}

int	ft_unset(t_shell *shell, t_command command)
{
	while (command.argv[1])
	{
		env_unset(shell, command.argv[1]);
		command.argv++;
	}
	return (0);
}

int	ft_pwd(t_shell *shell, t_command command)
{
	char	*path;

	(void) shell;
	(void) command;
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("el minishello: pwd: %s\n", strerror(errno));
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
