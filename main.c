/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:22 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 07:33:04 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// rename to nt_array_dup
// maybe create to nt_array_cpy for environement.c
static char	**ft_strsdup(char **strs)
{
	char	**dup;
	size_t	size;

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

static char	*prompt(t_shell *shell)
{
	char	*prompt;
	char	*user;
	char	*home;
	char	*path;
	bool	is_home;

	prompt = NULL;
	user = ft_get_env(shell, "USER", 4);
	home = ft_get_env(shell, "HOME", 4);
	path = getcwd(NULL, 0);
	is_home = !ft_strncmp(path, home, ft_strlen(home));
	if (user)
		prompt = ft_strdup(user);
	if (user && path)
		prompt = str_concat_consume(prompt, ":", 0);
	if (is_home)
		prompt = str_concat_consume(prompt,
				ft_strjoin("~", path + ft_strlen(home)), 2);
	else
		prompt = str_concat_consume(prompt, path, 0);
	prompt = str_concat_consume(prompt, "$ ", 0);
	free_str(&shell->prompt);
	shell->prompt = prompt;
	return (free_str(&user), free_str(&home), free_str(&path), prompt);
}

static void	run_loop(t_shell *shell)
{
	while (shell->running)
	{
		signals_main();
		shell->input = readline(prompt(shell));
		if (!shell->input)
			break ;
		signals_cmd();
		errno = 0;
		if (tokenize(shell) && lexer(shell->tokens) && commander(shell)
			&& errno == 0)
			executor(shell, shell->command_list);
		if (errno != 0)
			printf("el minishello: %s\n", strerror(errno));
		add_history(shell->input);
		free_shell(shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
		return (printf("Why R u running my shell with args ?😱\n"), 1);
	printf("WELCOME TO MiNI@\n\n");
	ft_bzero(&shell, sizeof(t_shell));
	shell.running = 1;
	shell.env = ft_strsdup(env);
	run_loop(&shell);
	free_str_array(shell.env);
	rl_clear_history();
	free_shell(&shell);
}
