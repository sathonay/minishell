/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:40:42 by alrey             #+#    #+#             */
/*   Updated: 2025/07/30 14:45:33 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*find_env_var(char *var, char **env)
{
	size_t	len;

	len = ft_strlen(var);
	while (*env)
	{
		if (ft_strncmp(*env, var, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

char	*find_exec(char *exec, char **env)
{
	char	*path;
	char	**paths;
	size_t	i;

	if (!exec)
		return (NULL);
	if (access((const char *) exec, X_OK) == 0)
		return (exec);
	if (*exec == '.' || *exec == '/')
		return (NULL);
	path = find_env_var("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strconcat(ft_strjoin(paths[i], "/"), exec);
		if (path && access((const char *) path, X_OK) == 0)
			return (free_str_array(paths), path);
		free_str(&path);
		i++;
	}
	return (free_str_array(paths), NULL);
}
