#include "shell.h"

static char *find_first(char *str, char *chars)
{
	char	*o_chars;

	o_chars = chars;
	while (*str)
	{
		while (*chars)
		{
			if (*chars == *str)
				return (str);
			chars++;
		}	
		chars = o_chars;
		str++;
	}
	return (str);
}

static void tokenization(t_shell *shell)
{
	char	*input;
	char	*close;
	(void) close;
	shell->argc = 0;
	input = shell->line;
	while (*input && *input == ' ') 
		input++;
	while (*input)
	{
		printf("%s\n", input);
		if (*input == ' ' && input[1] && input[1] != ' ')
			shell->argc++;
		else if (*input == '"')
			input = ft_strchr(input + 1, '"');
		else if (*input == '\'')
			input = ft_strchr(input + 1, '\'');
		input++;
	}
	printf("argc %d\n", shell->argc);
	input = shell->line;
	shell->argv = ft_calloc(sizeof(char *), shell->argc);
	while (*input)
	{
		while (*input && *input == ' ' && input[1] == ' ') 
			input++;
	}
}

/*static char *expand(t_shell *shell, char *input, bool dquote)
{
	char	*wend;

	if (!input)
		return (NULL);
	while (input)
	{
		if (*input == '$')
		{
			if (input[1] == '?')	
				return (ft_strjoin(shell->line, ft_itoa(shell->exit_code)));
			wend = input;
			while (ft_isalpha(*wend))
					wend++;
			shell->line = ft_strjoin(shell->line,
									ft_get_env(shell, input, end - input));
		}
		input = wend;
	}
	return ();
}*/

//___$__$_"__$___$___"__$___'____'
void lex(t_shell *shell)
{
	(void) shell;
	/*char	*input;
	char	*close;

	shell->line = NULL;
	input = shell->input;
	while (*input)
	{
		close = find_first(input, "$\'\"");
		if (*close == '\'')
			
		if (*close == '"')
		else
			expand(shell, input);
		input = close;
	}
	printf("%s\n", shell->line);*/
//	while (*input)
//	{
//		close = find_first(input, "$\'\"");
//		shell->line = ft_strjoin(shell->line,
//											ft_substr(input, 0, close - input));
//		input = close;
//		if (*input == '\'')
//		{
//			close = ft_strchrnul(input + 1, '\'');
//			shell->line = ft_strjoin(shell->line,
//										ft_substr(input, 0, close - input + 1));
//			if (!*close)
//				printf("quote\n");
//			input = close + 1;	
//		}
//		else if (*input == '"')
//		{
//			close = find_first(input + 1, "?\"");
//			if (*close && *close != '"')
//				shell->line = ft_strjoin(shell->line,
//										ft_substr(input, 0, close - input + 1));
//			printf("|%c|", *close);
//			while (*close == '?')
//			{
//				input = expand(shell, close);
//				close = find_first(input, "?\"");
//			}
//			close = ft_strchrnul(input + 1, '"');
//			shell->line = ft_strjoin(shell->line,
//										ft_substr(input, 0, close - input + 1));
//			if (*close == '\0')
//				printf("dquote\n");
//			input = close + 1;
//		}
//		else if (*close == '$' && (ft_isalpha(close[1]) || close[1] == '?'))
//			input = expand(shell, input + 1) + 1;
//	}
//	while (*input)
//	{
//		close = NULL;	
//		if (*input == '"')
//		{
//			close = ft_strchrnul(input + 1, '"');
//			while (++input < close)
//			{
//				if (*input == '$' && input[1] && input[1] != ' '
//					&& input[1] != '\'' && input[1] != '"' && input[1] != '$')
//					input = expand(shell, input + 1);
//				else
//					write(1, input, 1);
//			}
//		}
//		else if (*input == '\'')
//		{
//			close = ft_strchrnul(input + 1, '\'');
//			if (*close == '\'')
//			{
//				write(1, ++input, close - (input + 1));
//				input =	close + 1;
//			}
//		}
//		else if (*input == '$' && input[1] && input[1] != ' '
//				&& input[1] != '\'' && input[1] != '"' && input[1] != '$')
//			close = expand(shell, input + 1);
//		else
//			write(1, input, 1);
//		if (close != NULL)
//			input = close;
//		input++;
//	}
	//tokenization(shell);
//	while (*input)
//	{
//		close = NULL;	
//		if (*input == '"')
//		{
//			close = ft_strchrnul(input + 1, '"');
//			while (++input < close)
//			{
//				if (*input == '$' && input[1] && input[1] != ' '
//					&& input[1] != '\'' && input[1] != '"' && input[1] != '$')
//					input = expand(shell, input + 1);
//				else
//					write(1, input, 1);
//			}
//		}
//		else if (*input == '\'')
//		{
//			close = ft_strchrnul(input + 1, '\'');
//			if (*close == '\'')
//			{
//				write(1, ++input, close - (input + 1));
//				input =	close + 1;
//			}
//		}
//		else if (*input == '$' && input[1] && input[1] != ' '
//				&& input[1] != '\'' && input[1] != '"' && input[1] != '$')
//			close = expand(shell, input + 1);
//		else
//			write(1, input, 1);
//		if (close != NULL)
//			input = close;
//		input++;
//	}
}

