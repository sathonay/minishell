/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 02:28:12 by alrey             #+#    #+#             */
/*   Updated: 2025/08/26 03:02:34 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_env(t_shell *shell, char *str, size_t size)
{
	char	**env;

	if (size == 1 && *str == '?')
		return (ft_itoa(shell->exit_code));
	env = shell->env;
	while (*env)
	{
		if ((*env)[size] == '=' && ft_strncmp(*env, str, size) == 0)
			return (ft_strdup((*env) + size + 1));
		env++;
	}
	return (NULL);
}

bool	environement_format(char *input, size_t size)
{
	if (!ft_isalpha(*input) && *input != '_')
		return (0);
	input++;
	size--;
	while (size)
	{
		if (!ft_isalnum(*input) && *input != '_')
			return (0);
		input++;
		size--;
	}
	return (size == 0);
}

static size_t nt_array_size(void **array)
{
	size_t size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}

static int env_add(t_shell *shell, char *name, char *value)
{
	size_t	size;
	char	**env;

	size = nt_array_size((void **)shell->env);
	env = ft_calloc(1 + size + 1, sizeof(char *));
	env[0] = ft_strjoin(name, value);
	while (size--)
		env[1 + size] = shell->env[size];
	free(shell->env);
	shell->env = env;
	return (0);
}

int	env_set(t_shell *shell, char *name, char *value)
{
	size_t	size;
	char	**env;

	size = ft_strlen(name) - 1;
	env = shell->env;
	while (*env)
	{
		if ((*env)[size] == '=' && ft_strncmp(*env, name, size) == 0)
			break ;
		env++;
	}
	if (*env)
	{
		free(*env);
		*env = ft_strjoin(name, value);	
	}
	else
		env_add(shell, name, value);
	return (0);
}

int env_unset(t_shell *shell, char *name)
{
	size_t size;
	char	**env;

	size = ft_strlen(name);
	env = shell->env;
	while (*env)
	{
		if ((*env)[size] == '=' && ft_strncmp(*env, name, size) == 0)
		{
			free(*env);
			break;
		}
		env++;
	}
	if (!*env)
		return (1);
	while (*env)
	{
		*env = env[1];
		env++;
	}
	return (0);
}