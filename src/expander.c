/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:17:27 by alrey             #+#    #+#             */
/*   Updated: 2025/07/29 19:17:27 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*str_concat_consume(char *str1, char *str2, int str_to_consome)
{
	char	*concat;
	
	concat = ft_strjoin(str1, str2);
	if (str_to_consome == 2)
	{
		free_str(&str2);
		free_str(&str1);
	}
	else if (str_to_consome == 1)
		free_str(&str2);
	else if (str_to_consome == 0)
		free_str(&str1);
	return (concat);
} 

static char	*expand_env_var(t_shell *shell, t_token_stack *token)
{
	char	*token_str;
	size_t	l;
	char	*str;
	
	if (token->type == QSTR)
		return (ft_substr(token->start, 0, token->end - token->start));
	str = NULL;
	token_str = token->start;
	while (token_str < token->end)
	{
		if (*token_str == '$') {
			token_str++;
			l = 0;
			while (ft_isalnum(token_str[l]) || token_str[l] == '_')
				l++;
			if (*token_str == '?')
				l++;
			str = str_concat_consume(str, ft_get_env(shell, token_str, l), 2);
			token_str += l;
			continue;
		}
		str = str_concat_consume(str, ft_substr(token_str, 0, 1), 2);
		token_str++;
	}
	return (str);
}

static void	**ft_list_to_array(t_list *list)
{
	void	**array;
	size_t	i;
	if (!list)
		return (NULL);
	array = ft_calloc(ft_lstsize(list) + 1, sizeof(void *));
	if (!array)
		return (NULL);
	i = 0;
	while (list) {
		array[i] = list->content;
		list = list->next;
		i++;
	}
	return (array);
}
/*void	expander(t_shell *shell)
{
	t_token_stack	*token;
	t_list			*argv_list;
	char			*str;
	(void) ft_list_to_array(NULL);
	token = shell->tokens;
	argv_list = NULL;
	while (token)
	{
		token = get_first_token(token, STR | QSTR | DQSTR | PIPE);
		if (!token)
			break ;
		str = expand_env_var(shell, token);
		while (token->next && (token->next->type & (STR | QSTR | DQSTR)) > 0)
		{
			str = ft_strjoin((char *)  str, expand_env_var(shell, token->next));
			token = token->next;
		}
		ft_lstadd_back(&argv_list, ft_lstnew(expand_env_var(shell, token)));
		token = token->next;
	}
}*/

t_token_stack	*expande(t_shell *shell, t_token_stack *token, t_command *command)
{
	char			*str;

	str = NULL;
	(void) ft_list_to_array(NULL);
	if (token && (token->type & (STR | QSTR | DQSTR)))
	{
		str = expand_env_var(shell, token);
		while (token->next && (token->next->type & (STR | QSTR | DQSTR)))
		{
			if (!str)
				return (NULL); 
			str = ft_strjoin((char *)  str, expand_env_var(shell, token->next));
			if ((token->next->type & (STR | QSTR | DQSTR)) == 0)
				break;
			token = token->next;
		}
		ft_lstadd_back(&command->argv_builder, ft_lstnew(str));
		printf("argv add %s\n", str);
		return (token);
	}
	return (NULL);
}


/*
char **argv = (char **) ft_list_to_array(argv_list);
	int size = ft_lstsize(argv_list);
	ft_lstclear(&argv_list, NULL);
	char *path = find_exec(*argv, shell->env);

	if (!ft_strcmp(*argv, "pwd"))
		ft_pwd(size, argv, shell->env);
	else if (!ft_strcmp(*argv, "cd"))
		ft_cd(size, argv, shell->env);
	else if (!ft_strcmp(*argv, "exit"))
	{
		char **argv_o = argv;
		while (*argv) {
			free(*argv);
			argv++;
		}
		free(argv_o);
		ft_exit(shell);
	}
	else if (path) {
		int	wstatus;
		pid_t	fid;

		fid = fork();
		if (fid == 0)
			execve(path, argv, shell->env);
		waitpid(fid, &wstatus, 0);
		free(path);
	}
	char **argv_o = argv;
	printf("argv list:\n");
	while (*argv) {
		printf("	|%s|\n", *argv);
		free(*argv);
		argv++;
	}
	free(argv_o);
*/

