/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:10:55 by alrey             #+#    #+#             */
/*   Updated: 2025/07/21 15:27:31 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static int get_command_count(t_token_stack *token) {
	int count;
	
	count = 1;
	while (token->type != NONE) {
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
}

static void tokens_to_commands(t_shell *shell) {
	t_token_stack *token;
	int command_count;

	token = shell->tokens;
	commands
	while (token)
	{
		printf("size %d\n", token->end - token->start);
		printf("type %d\n", token->type);
		write(1, token->start, token->end - token->start);
		write(1, "\n", 1);
		token = token->next;
	}
}*/

static t_token_stack	*extract_command(t_token_stack *token)
{
	while (token->type != NONE || token->type != PIPE)
	{
		
	}
	return (token);
}

void executor(t_shell *shell)
{
	
}
