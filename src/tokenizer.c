/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:40:46 by alrey             #+#    #+#             */
/*   Updated: 2025/05/17 00:40:49 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_token_length(enum e_token_type type)
{
	if (type == PIPE || type == O_FILE || type == I_FILE
		|| type == STR || type == QSTR || type == DQSTR || type == EMPTY)
		return (1);
	else if (type == HERE_DOC || type == O_FILE_APPEND)
		return (2);
	return (0);
}

static t_token_stack	*new_token(char *start, char *end,
										enum e_token_type type)
{
	t_token_stack	*token;

	token = malloc(sizeof(t_token_stack));
	if (token == NULL)
		return (NULL);
	token->start = start;
	token->end = end;
	token->type = type;
	token->next = NULL;
	return (token);
}

static enum e_token_type	to_token_type(char *input)
{
	if (*input == '|')
		return (PIPE);
	else if (*input == '<' && input[1] == '<')
		return (HERE_DOC);
	else if (*input == '<')
		return (I_FILE);
	else if (*input == '>' && input[1] == '>')
		return (O_FILE_APPEND);
	else if (*input == '>')
		return (O_FILE);
	else if (*input == '\'')
		return (QSTR);
	else if (*input == '"')
		return (DQSTR);
	else if (*input && *input <= ' ')
		return (EMPTY);
	else if (*input > ' ' && *input <= '~')
		return (STR);
	return (NONE);
}

static int	extract_token(t_shell *shell, char **head)
{
	t_token_stack	*token;

	token = new_token(*head, *head + 1, to_token_type(*head));
	if (token == NULL || token->type == NONE)
		return (0);
	if (token->type == STR || token->type == EMPTY)
	{
		while (*token->end && to_token_type(token->end) == token->type)
			token->end++;
		*head = token->end;
	}
	else if (token->type == DQSTR || token->type == QSTR)
	{
		token->start++;
		while (*token->end && to_token_type(token->end) != token->type)
			token->end++;
		if (!*token->end)
			return (0);
		*head = token->end + 1;
	}
	else
		*head = token->end;
	append_token(shell, token);
	return (1);
}

int	tokenize(t_shell *shell)
{
	char	*input;

	if (!shell->input)
		return (0);
	input = shell->input;
	while (*input && extract_token(shell, &input))
		;
	return (*input == 0);
}
