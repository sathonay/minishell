/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:38:20 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 08:19:59 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_command(t_command *command)
{
	ft_lstclear(&command->argv_builder, free);
	free_str_array(command->argv);
	free_str(&command->executable_path);
	free_str(&command->outfile.path);
	free_str(&command->infile.path);
	free_str(&command->infile.eof);
	free(command);
}

void	clear_command_stack(t_shell *shell)
{
	ft_lstclear(&shell->command_list, (void *) clear_command);
}

static void	free_token_stack(t_token_stack **tokens)
{
	t_token_stack	*token;

	if (*tokens)
	{
		while (*tokens)
		{
			token = *tokens;
			*tokens = token->next;
			free(token);
		}
		*tokens = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	clear_command_stack(shell);
	free_str(&shell->input);
	free_str(&shell->prompt);
	free_token_stack(&shell->tokens);
}
