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
	return (!failed);
}
//_______|____
//___|___|____

static bool	check_pipes(char *input)
{
	size_t	count;
	bool	pipe_presence;

	count = 0;
	pipe_presence = 0;
	while (*input)
	{
		if (*input == '|')
		{
			pipe_presence = 1;
			if (count == 0)
				break;
			count = 0;
		}
		else if (*input && *input > ' ')
			count++;
		input++;
	}
	printf("count: %d", count);
	if (pipe_presence && !count)
		dprintf(2, "syntax error: pipe not pipeing. 🥱");
	return (!pipe_presence ||  count > 0);
}

bool syntax_valid(char *input)
{
	return (check_quotes(input) && check_pipes(input));
}
