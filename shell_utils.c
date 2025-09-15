/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:01:51 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 15:05:32 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_chdir(t_shell *shell, char *path)
{
	int		return_code;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		env_set(shell, "OLDPWD", pwd);
		free(pwd);
	}
	return_code = chdir(path);
	if (return_code == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			env_set(shell, "PWD", pwd);
			free(pwd);
		}
	}
	return (return_code);
}
