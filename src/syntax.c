#include "shell.h"

static bool check_quotes(char *input)
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

bool syntax_valid(char *input)
{
	return (!check_quotes(input));
}