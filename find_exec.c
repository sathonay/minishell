
#include "libft/libft.h"

void	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_str_array(char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
		free(strs[i++]);
	if (strs)
		free(strs);
}

static char	*find_env_var(char *var, char **env)
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
char	*find_exec(char *exec, char **env)
{
	char	*path;
	char	**paths;
	size_t	i;

	if (!exec)
		return (NULL);
	if (access((const char *) exec, X_OK) == 0)
		return (exec);
	if (*exec == '.' || *exec == '/')
		return (NULL);
	path = find_env_var("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strconcat(ft_strjoin(paths[i], "/"), exec);
		if (path && access((const char *) path, X_OK) == 0)
			return (free_str_array(paths), path);
		free_str(&path);
		i++;
	}
	return (free_str_array(paths), NULL);
}
int main(int argc, char **argv, char **env)
{
	printf("%s", find_exec(argv[1], env));
	return (0);
}
