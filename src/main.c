/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:22 by alrey             #+#    #+#             */
/*   Updated: 2025/04/17 08:10:09 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void ft_free_strs(char **strs)
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

static void	run_loop(t_shell *shell)
{
	while (shell->running)
	{
		shell->input = readline(shell->prompt);
		if (!shell->input)
			break;
		if (!syntax_valid(shell->input))
			dprintf(2, "syntax failed\n");
		shell->line = NULL;
		expand(shell);
		printf("line : |%s|\n", shell->line);
		
		if (ft_strncmp(shell->input, "exit", 5) == 0)
			shell->running = 0;
		if (ft_strncmp(shell->input, "env", 4) == 0)
			ft_env(shell);
		if (ft_strncmp(shell->input, "export", 7) == 0)
			ft_export(shell);
		add_history(shell->input);
		ft_free(&shell->input);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (argc > 1)
		return(dprintf(2, "Why R u running my shell with args ?😱\n"), 1);
	t_shell shell;
	shell.running = 1;
	shell.prompt = "mini@> ";
	shell.env = ft_strsdup(env);
	shell.input = NULL;
	run_loop(&shell);
	ft_free(&shell.input);
	ft_free_strs(shell.env);
	rl_clear_history();
}
