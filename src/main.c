/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:22 by alrey             #+#    #+#             */
/*   Updated: 2025/04/10 15:58:49 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

static void ft_free_strs(char **strs)
{
	size_t size;

	size = 0;
	while (strs[size])
		free(strs[size++]);
	free(strs);
}



static char **ft_strsdup(char **strs)
{
	char **dup;
	size_t size;

	size = 0;
	while (strs[size])
		size++;
	dup = malloc((size + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	dup[size] = NULL;
	while (size--)
		dup[size] = ft_strdup(strs[size]);
	return (dup);
}



int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_shell shell;
	shell.running = 1;
	shell.prompt = "mini@> ";
	shell.env = ft_strsdup(env);
	while (shell.running)
	{
		shell.input = readline(shell.prompt);
		if (!shell.input)
			break;
		if (ft_strncmp(shell.input, "exit", 5) == 0)
			shell.running = 0;
		if (ft_strncmp(shell.input, "env", 4) == 0)
			ft_env(shell);
		if (ft_strncmp(shell.input, "export", 7) == 0)
			ft_export(&shell);
		add_history(shell.input);
		ft_free(&shell.input);
	}
	ft_free(&shell.input);
	ft_free_strs(shell.env);
	rl_clear_history();
}
