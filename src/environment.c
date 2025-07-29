#include "shell.h"

char	*ft_get_env(t_shell *shell, char *str, size_t size)
{
	char **env;

	env = shell->env;
	while(*env)	
	{
		if ((*env)[size] == '=' && ft_strncmp(*env, str, size) == 0)
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

char	*env_get(char **env, char *var)
{
	size_t	len;

	len = ft_strlen(var);
	while (*env)
	{
		if (ft_strncmp(*env, var, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}