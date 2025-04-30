#include "shell.h"

static bool	check_quotes(char *input)
{
	bool failed;
	char limiter;

	failed = 0;
	while (*input)
	{
		if (*input == '\'' ||*input == '"')
		{
			limiter = *input;
			failed = 1;
			input = ft_strchrnul(input + 1, limiter);
			if (*input == limiter)
				failed = 0;
			else
				break ;
		}
		input++;
	}
	if (failed)
		dprintf(2, "syntax error: quote not quoting properly. 🥱");
	return (failed);
}
//_______|____
//___|___|____
static bool	check_pipes(char *input)
{
	bool	failed;

	failed = 1;
	while (*input && *input <= ' ')
		input++;
	if (*input > ' ')	
		failed = 0;
	while (*input)
	{
		if (*input == '|')
		{
			failed = 1;
			while (*input && *input <= ' ')
				input++;
			if (*input > ' ')	
				failed = 0;
		}
		input++;
	}
	if (failed)
		dprintf(2, "syntax error: pipe not pipeing. 🥱");
	return (failed);
}


bool syntax_valid(char *input)
{
	return (!check_quotes(input) && !check_pipes(input));
}
