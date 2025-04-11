#include "shell.h"

static char	*ft_get_env(t_shell *shell, char *str, int size)
{
	char **env;

	env = shell->env;
	while(*env)	
	{
		if (ft_strncmp(*env, str, size) == 0 && (*env)[size] == '=')
		{
			return (ft_strdup((*env) + size));
		}
		env++;
	}
	return (NULL);
}
static void expand(t_shell *shell, char *input)
{
	char	*break;
	char	*line;
	size_t	word;

	line = NULL;
	(void)line;
	(void)shell;
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
}

void lex(t_shell *shell)
{
	char	*input;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	input = shell->input;
	while (*input)
	{
		if (*input == '$' && (quotes[0] % 2 || quotes[0] == 0))
			expand(shell, input);
		else if (*input == '"')
			expand(shell, input + 1);
			quotes[0] += 1;
		else if (*input == '\'')
			quotes[1] += -1;
		input++;
	}
	printf("%d %d\n", quotes[0], quotes[1]);
}

