#include "shell.h"

char	*ft_get_env(t_shell *shell, char *str, int size)
{
	char **env;

	env = shell->env;
	while(*env)	
	{
		if (ft_strncmp(*env, str, size) == 0 && (*env)[size] == '=')
			return (ft_strdup((*env) + size + 1));
		env++;
	}
	return (NULL);
}

bool	environement_format(char *input, size_t size)
{
	if (!ft_isalpha(*input) && *input != '_')
		return (0);
	input++;
	size--;
	while (size)
	{
		if (!ft_isalnum(*input) && *input != '_')
			return (0);
		input++;
		size--;
	}	
	return (size == 0);
}

bool	environement_set(char *key, char *value)
{
	
}

char	**environement_toarray(t_shell *shell)
{
	
}
