#include "shell.h"

static char	*ft_get_env(t_shell *shell, char *str, int size)
{
	char **env;

	env = shell->env;
	while(*env)	
	{
		if (ft_strncmp(*env, str, size) == 0 && (*env)[size] == '=')
		{
			printf("%s\n",	(*env) + size);
			return (ft_strdup((*env) + size));
		}
		env++;
	}
	return (NULL);
}

static char *expand(t_shell *shell, char *input)
{
	char	*end;
	char	*line;
	size_t	word;

	line = NULL;
	end = input;
	(void)shell;
	(void)line;
	while (*end && *end != ' ' && *end != '"' && *end != '$')
		word++;
	while (*input)
	{
		word = 0;
		if (*input == '$')
		{
			input++;
			while (input[word] && input[word] != ' ' && input[word] != '"')
				word++;
			printf("%p\n", ft_get_env(shell, input, word));
			input += word;
		}
		if (*input == '"')
			break ;
		input++;
	}
	return (end);
}

void lex(t_shell *shell)
{
	char	*input;
	char	*close;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	input = shell->input;
	while (*input)
	{
		close = NULL;	
		if (*input == '"')
		{
			close = ft_strchr(input + 1, '"');
			if (close != NULL)
				write(1, input + 1, close - (input + 1));
		}
		else if (*input == '\'')
		{
			close = ft_strchr(input + 1, '\'');
			if (close != NULL)
				write(1, input + 1, close - (input + 1));
		}
		else
			write(1, input, 1);
		if (close != NULL)
			input = close;
		input++;
	}
//	while (*input)
//	{
//		if (*input == '$' && (quotes[0] % 2 || quotes[0] == 0) && !(quotes[1] % 2))
//			expand(shell, input);
//		else if (*input == '"')
//			quotes[0] += 1;
//		else if (*input == '\'')
//			quotes[1] += -1;
//		if (*input == '"' || *input == '\'')
//			last_quote = *input;
//		input++;
//	}
	printf("%d %d\n", quotes[0], quotes[1]);
}

