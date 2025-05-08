#include "shell.h"

t_token_stack	*new_token(char *start, char *end, enum e_token_type type)
{
	t_token_stack	*token = malloc(sizeof(t_token_stack));
	if (token == NULL)
		return (NULL);
	token->start = start;
	token->end = end;
	token->type = type;
	return (token);
}
//_____aaaabbcc_____|

enum e_token_type to_token_type(char *input)
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
	else if (*input && *input <= ' ')
		return (EMPTY);
	else if (*input > ' ' && *input < *input <= '~')
		return (STR);
	return (NONE);
}

int	get_token_length(enum e_token_type type)
{
	if (type == PIPE || type == O_FILE || type == I_FILE)
		return (1);
	else if (type == HERE_DOC || type == O_FILE_APPEND)
		return (2);
	else if (type == EMPTY || type == STR)
		return (-1);
	return (0);
}

int	extract_token(t_shell *shell, char **head)
{
	t_token_stack	*token;

	token = new_token(*head, *head, to_token_type(*head));
	if (token == NULL || token->type == NONE)
		return (0);
	*head = ++token->end;
	printf("first %d\n", token->type);
	if (token->type != STR && token->type != EMPTY)
		return (1);
	while (to_token_type(token->end) == STR
			|| to_token_type(token->end) == EMPTY)
	{
		token->type = to_token_type(token->end);
		token->end++;
	}
	printf("second %d\n", token->type);
	*head = token->end;
	return (1);
}

int	tokenize(t_shell *shell)
{
	char	*input;

	if (!shell->input)
		return 0;
	input = shell->input;
	while (*input && extract_token(shell, &input))
		;
	return (*input == 0);
}
