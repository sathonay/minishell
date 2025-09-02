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

char	**split_first(char *str, char sep)
{
	char	*match_ptr;
	char	**split;

	match_ptr = str;
	split = ft_calloc(2 + 1, sizeof(char *));
	if(!split)
		return (NULL);
	while (*match_ptr && *match_ptr != sep)
		match_ptr++;
	if (!*match_ptr)
		split[0] = ft_strdup(str);
	else
	{
		split[0] = ft_substr(str, 0, match_ptr - str);
		split[1] = ft_strdup(match_ptr + 1);
	}
	return (split);
}


static char	*str_concat_consume(char *str1, char *str2, int str_to_consome)
{
	char	*concat;

	concat = ft_strjoin(str1, str2);
	if (str_to_consome == 2)
	{
		free_str(&str2);
		free_str(&str1);
	}
	else if (str_to_consome == 1)
		free_str(&str2);
	else if (str_to_consome == 0)
		free_str(&str1);
	return (concat);
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

int ft_unset(t_shell *shell, t_command command)
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

int	ft_echo(t_shell *shell, t_command command)
{
	bool print_newline;

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

int	ft_exit(t_shell *shell, t_command command)
{
	(void) command;
	printf("exiting\n");
	free_shell(shell);
	rl_clear_history();
	exit(0);
	return (0);
}
