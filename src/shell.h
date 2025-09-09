/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:56 by alrey             #+#    #+#             */
/*   Updated: 2025/09/06 13:42:18 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

enum	e_token_type
{
	NONE			= 0b0000000000,
	EMPTY			= 0b0000000010,
	STR				= 0b0000000100,
	QSTR			= 0b0000001000,
	DQSTR			= 0b0000010000,
	PIPE			= 0b0000100000,
	HERE_DOC		= 0b0001000000,
	I_FILE			= 0b0010000000,
	O_FILE			= 0b0100000000,
	O_FILE_APPEND	= 0b1000000000,
	REDIRECTIONS	= 0b1111100000,
	ALL_NON_EMPTY	= 0b1111111100,
};

typedef enum e_token_type	t_token_type;

typedef struct s_token_stack
{
	char					*start;
	char					*end;
	enum e_token_type		type;
	struct s_token_stack	*next;
}			t_token_stack;

typedef struct s_redirect
{
	t_token_type	type;
	int				fd;
	char			*path;
	char			*eof;
}			t_redirect;

typedef struct s_command
{
	pid_t		pid;
	t_list		*argv_builder;
	t_redirect	infile;
	int			argc;
	char		**argv;
	char		*executable_path;
	t_redirect	outfile;
}				t_command;

typedef struct s_shell
{
	int				exit_code;
	t_token_stack	*tokens;
	t_command		*commands;
	char			running;
	char			*prompt;
	char			*input;
	char			*line;
	int				argc;
	char			**argv;
	char			**env;
	t_list			*command_list;

}			t_shell;

typedef struct s_expander_result
{
	t_token_stack	*end;
	char			*str;
}	t_expander_result;

bool				lexer(t_token_stack *token);

/*
	Libft+
*/

char	*str_concat_consume(char *str1, char *str2, int str_to_consome);

char	**str_split_first(char *str, char sep);

void	**lst_to_array(t_list *lst);

size_t	nt_array_size(void **array);

char				*ft_strldup(const char *s1, size_t len);

/*
Bult in
*/

int					ft_env(t_shell *shell, t_command command);

int					ft_export(t_shell *shell, t_command command);

int					ft_unset(t_shell *shell, t_command command);

int					ft_echo(t_shell *shell, t_command command);

int					ft_cd(t_shell *shell, t_command command);

int					ft_pwd(t_shell *shell, t_command command);

int					ft_exit(t_shell *shell, t_command command);

void				lex(t_shell *shell);

char				*ft_get_env(t_shell *shell, char *str, size_t size);


int	env_set(t_shell *shell, char *name, char *value);

int env_unset(t_shell *shell, char *name);

bool				syntax_valid(char *input);

int					expand(t_shell *shell);

/*
	token.c
*/

void				append_token(t_shell *shell, t_token_stack *token);

t_token_stack		*get_first_token(t_token_stack *token, t_token_type type);

char				*get_token_str_type(t_token_type type);

/*
	tokenizer.c
*/

int					tokenize(t_shell *shell);

char				*find_exec(char *exec, char **env);

//void	expander(t_shell *shell);

t_expander_result	expande(t_shell *shell, t_token_stack *token);

bool				commander(t_shell *shell);

void				executor(t_shell *shell, t_list *command_stack);

/*
	Free related
*/

void				clear_command(t_command *command);

void				clear_command_stack(t_shell *shell);

void				free_str(char **str);

void				free_str_array(char **strs);

void				free_shell(t_shell *shell);

void				signals_main(void);

void				signals_cmd(void);

void				dup_in_and_out(int fd[2]);

int					dup2_close_old(int old, int new);

#endif
