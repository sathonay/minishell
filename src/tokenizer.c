#include "shell.h"

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
}

//_____ | HERE_DOC << EOF

int tokenize(t_shell *shell)
{
	char	*input;
	char	*end;

	if (!shell->input)
		return ;
	input = shell->input;
	end = input;
	while (*input)
	{
		end = 
		input = end;
	}
	return (1);
}
