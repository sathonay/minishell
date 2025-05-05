#include "shell.h"

t_token_stack	new_token(char *start, char *end, enum e_token_type type)
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
e_token_type str_or_empty_type(char *input)
{
	input
	return ();
}

e_token_type to_token_type(char *input)
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
	else if (*input <= ' ')
		return (EMPTY);
	else if (*input > ' ' && < *input <= '~')
		return (STR);
	return (NONE);
}

int	extract_token(t_shell *shell, char **head)
{
	t_token_stack	*token;

	token = new_token(*head, *head, to_token_type(*head));
	if (token == NULL)
		return (0);
	if (token->type != STR && token->type != EMPTY)
		return (1);
	while (to_token_type(token->end) == STR
			|| to_token_type(token->end) == EMPTY)
	{
		token->type = to_token_type(token->end);
		token->end++;
	}
	head = token->end++;
	return (1);
}

int	tokenize(t_shell *shell)
{
	char	*input;

	if (!shell->input)
		return ;
	input = shell->input;
	while (*input && extract_token(input))
		;
	return (*input == 0);
}
