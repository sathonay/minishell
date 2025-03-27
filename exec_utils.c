/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:30:36 by alrey             #+#    #+#             */
/*   Updated: 2025/03/27 01:32:47 by alrey            ###   ########.fr       */
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

static char	*ft_strconcat(char *str1, char *str2)
{
	char	*concat;

	concat = ft_strjoin(str1, str2);
	if (!concat)
		return (str1);
	if (str1)
		free(str1);
	return (concat);
}

static char	*find_exec(char *exec, char **env)
{
	char	*path;
	char	**paths;
	size_t	i;

	if (access((const char *) exec, X_OK) == 0)
		return (exec);
	path = find_env_var("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strconcat(ft_strjoin(paths[i], "/"), exec);
		if (path && access((const char *) path, X_OK) == 0)
		{
			free_str_array(paths);
			return (path);
		}
		free_str(&path);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

pid_t	fork_exec(char *cmd, char **env, int fdin, int fdout)
{
	pid_t	fid;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!*args)
		return (free_str_array(args), 0);
	cmd = find_exec(*args, env);
	fid = fork();
	if (fid != 0)
		return (fid);
	if (cmd)
	{
		dup2(fdin, 0);
		dup2(fdout, 1);
		execve(cmd, args + 1, env);
	}
	else
		dprintf(2, "command not found: %s\n", *args);
	free_str_array(args);
	return (fid);
}
