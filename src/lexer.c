#include "shell.h"

static char	*ft_get_env(t_shell *shell, char *str, int size)
{
	char **env;

	env = shell->env;
	while(*env)	
	{
		if (ft_strncmp(*env, str, size) == 0 && (*env)[size] == '=')
		{
			write(1, (*env) + size + 1, ft_strlen((*env) + size + 1));
			return (ft_strdup((*env) + size + 1));
		}
		env++;
	}
	return (NULL);
}

static char *expand(t_shell *shell, char *input)
{
	char	*end;
	char	*line;

	line = NULL;
	(void)shell;
	(void)line;
	end = input;
	while (end[1] && end[1] != ' ' && end[1] != '\''  && end[1] != '"' && end[1] != '$')
		end++;
	ft_get_env(shell, input, end - input + 1);
	return (end);
}

void lex(t_shell *shell)
{
	char	*input;
	char	*close;

	input = shell->input;
	while (*input)
	{
		close = NULL;	
		if (*input == '"')
		{
			close = ft_strchrnul(input + 1, '"');
			while (++input < close)
			{
				if (*input == '$')
					input = expand(shell, input + 1);
				else
					write(1, input, 1);
			}
		}
		else if (*input == '\'')
		{
			close = ft_strchrnul(input + 1, '\'');
			if (*close == '\'')
			{
				write(1, ++input, close - (input + 1));
				input =	close + 1;
			}
		}
		else if (*input == '$')
			close = expand(shell, input + 1);
		else
			write(1, input, 1);
		if (close != NULL)
			input = close;
		input++;
	}
}

