/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:50 by alrey             #+#    #+#             */
/*   Updated: 2025/08/26 18:04:38 by alrey            ###   ########.fr       */
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

int	ft_export(t_shell *shell)
{
	char	**dup;
	size_t	size;

	size = 0;
	while (shell->env[size])
		size++;
	dup = malloc((1 + size + 1) * sizeof(char *));
	if (!dup)
		return (1);
	dup[0] = ft_strjoin("TEST=", "coucou");
	dup[size + 1] = NULL;
	while (size--)
		dup[size + 1] = ft_strdup(shell->env[size]);
	free_str_array(shell->env);
	shell->env = dup;
	return (0);
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

int	ft_exit(t_shell *shell, t_command command)
{
	(void) command;
	printf("exiting");
	free_shell(shell);
	rl_clear_history();
	exit(0);
	return (0);
}
