/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:38:20 by alrey             #+#    #+#             */
/*   Updated: 2025/07/30 08:57:13 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_str_array(char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
		free(strs[i++]);
	if (strs)
		free(strs);
}

void	free_token_stack(t_shell *shell)
{
	t_token_stack *token;

	if (shell->tokens)
	{
		while (shell->tokens)
		{
			token = shell->tokens;
			shell->tokens = token->next;
			free(token);
		}
		shell->tokens = NULL;	
	}
}
void	free_shell(t_shell *shell)
{
	free_str(&shell->prompt);
	free_token_stack(shell);
}