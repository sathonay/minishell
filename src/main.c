/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:22 by alrey             #+#    #+#             */
/*   Updated: 2025/07/30 08:33:58 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void print_token_stack(t_shell *shell)
{
	t_token_stack *token;
	
	token = shell->tokens;
	while (token)
	{
		printf("pointer %p\n", token);
		printf("size %ld\n", token->end - token->start);
		printf("type %s\n", get_token_str_type(token->type));
		printf("next %p\n", token->next);
		write(1, token->start, token->end - token->start);
		write(1, "\n", 1);
		token = token->next;
	}
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
	else if (str_concat_consume == 0)
		free_str(&str1);
	return (concat);
} 

char	*prompt(t_shell *shell)
{
	char	*prompt;
	char	*user;
	char	*home;
	char	*path; 
	bool 	is_home;

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
		prompt = str_concat_consume(prompt, ft_strjoin("~", path + ft_strlen(home)), 2);
	else
		prompt = ft_strjoin(prompt, path);
	prompt = str_concat_consume(prompt, "$ ", 0);
	return (free_str(&user), free_str(&home), free_str(&path), prompt);
}

static void	run_loop(t_shell *shell)
{
	while (shell->running)
	{
		shell->tokens = NULL;
		shell->input = readline(prompt(shell));
		if (!shell->input)
			break;
		//if (syntax_valid(shell->input))
		if (!tokenize(shell))
		{
			printf("tokeninzation failed");
		}
		shell->line = NULL;
		//expand(shell);
		//printf("line : |%s|\n", shell->line);
		//print_token_stack(shell);
		/*t_token_stack *token;

		token = shell->tokens;
		while (token)
		{
			printf("token type: %s\n", get_token_str_type(token->type));
			token = token->next;
		}*/

		//printf("------------------\n");
		expander(shell);
		//printf("------------------\n");
		
		if (get_first_token(shell->tokens, DQSTR))
		{
			printf("found dqstr\n");
		}
		
		if (ft_strncmp(shell->input, "exit", 5) == 0)
			shell->running = 0;
		if (ft_strncmp(shell->input, "env", 4) == 0)
			ft_env(1, NULL, shell->env);
		if (ft_strncmp(shell->input, "export", 7) == 0)
			ft_export(shell);
		add_history(shell->input);
		free_str(&shell->input);
		free_token_stack(shell);
	}
	rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (argc > 1)
		return(dprintf(2, "Why R u running my shell with args ?😱\n"), 1);
	t_shell shell;

	printf("WELCOME TO MiNI@\n\n");

	shell.running = 1;
	shell.prompt = "mini@> ";
	shell.env = ft_strsdup(env);
	shell.input = NULL;
	run_loop(&shell);
	free_str(&shell.input);
	free_str_array(shell.env);
	rl_clear_history();
}
