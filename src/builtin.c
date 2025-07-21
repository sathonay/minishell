/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:50 by alrey             #+#    #+#             */
/*   Updated: 2025/07/21 15:33:30 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_env(int argc, char **argv, char**env)
{
	if (!env)
		return (0);
	while(*env)
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

int ft_exit(t_shell *shell)
{
	(void)shell;
	return (0);
}
