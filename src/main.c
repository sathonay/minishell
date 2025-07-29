/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:22 by alrey             #+#    #+#             */
/*   Updated: 2025/07/29 22:47:58 by alrey            ###   ########.fr       */
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
		printf("size %ld\n", token->end - token->start);
		printf("type %d\n", token->type);
		write(1, token->start, token->end - token->start);
		write(1, "\n", 1);
		token = token->next;
	}
}
static void	run_loop(t_shell *shell)
{
	while (shell->running)
	{
		shell->tokens = NULL;
		shell->input = readline(shell->prompt);
		if (!shell->input)
			break;
		//if (syntax_valid(shell->input))
		if (!tokenize(shell))
		{
			printf("tokeninzation failed");
		}
		shell->line = NULL;
		//expand(shell);
		printf("line : |%s|\n", shell->line);
		print_token_stack(shell);
		/*t_token_stack *token;

		token = shell->tokens;
		while (token)
		{
			printf("token type: %s\n", get_token_str_type(token->type));
			token = token->next;
		}*/

		printf("------------------\n");
		expander(shell);
		printf("------------------\n");
		
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

	shell.running = 1;
	shell.prompt = "mini@> ";
	shell.env = ft_strsdup(env);
	shell.input = NULL;
	run_loop(&shell);
	free_str(&shell.input);
	free_str_array(shell.env);
	rl_clear_history();
}
