#include "shell.h"

static char *find_first(char *str, char *chars)
{
  char *o_chars;

  o_chars = chars;
  while (*str) {
    while (*chars) {
      if (*chars == *str)
        return (str);
      chars++;
    }
    chars = o_chars;
    str++;
  }
  return (str);
}

char *extract_str(t_shell *shell, char *input)
{
  char *wend;

  dprintf(2, "extract_str %s\n", input);
  wend = input;
  while (*wend && *wend != '\'')
    wend++;
  shell->line = ft_strjoin(shell->line, ft_substr(input, 0, wend - input));
  if (*wend == '\'')
    wend++;
  return (wend);
}


char  *to_expand(t_shell *shell, char *input)
{
  char *wend;
  
  wend = input;
  if (*wend == '?')
  {
    shell->line = ft_strjoin(shell->line, ft_itoa(shell->exit_code));
    return (++wend);
  }
  while (ft_isalnum(*wend) || *wend == '_')
    wend++;
  shell->line = ft_strjoin(shell->line, ft_get_env(shell, input, wend - input));
  return (++wend);
}

char *expand_str(t_shell *shell, char *input)
{
  char *wend;

  dprintf(2, "expand_str %s\n", input);
  wend = input;
  while (*input) 
  {
      if (!*wend || *wend == '"' || *wend == '\'')
        break ;
      else if (*wend == '$')
      {
        shell->line = ft_strjoin(shell->line, ft_substr(input, 0, wend - input));
        input = to_expand(shell, ++wend);
        wend = input;
      }
      else
        wend++;
  }
  shell->line = ft_strjoin(shell->line, ft_substr(input, 0, wend - input));
  if (*wend == '"' || *wend == '\'')
    wend++;
  return (wend);
}

int expand(t_shell *shell)
{
  char	*input;
  char	*close;
  
  input = shell->input;
  while (input && *input) {
  		if (*input == '\'')
        input = extract_str(shell, input + 1);
  		else if (*input == '"')
  			input = expand_str(shell, input + 1);
  		else
        input = expand_str(shell, input);
      if (!*input)
        break;
  }
  return (input != NULL);
}
