/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:56 by alrey             #+#    #+#             */
/*   Updated: 2025/07/18 09:14:10 by alrey            ###   ########.fr       */
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

typedef	struct s_lexer
{

}			t_lexer;

enum	e_token_type
{
	NONE			= 0x0000000000,
	EMPTY			= 0x0000000010,
	STR				= 0x0000000100,
	QSTR			= 0x0000001000,
	DQSTR			= 0x0000010000,
	PIPE			= 0x0000100000,
	HERE_DOC		= 0x0001000000,
	I_FILE			= 0x0010000000,
	O_FILE			= 0x0100000000,
	O_FILE_APPEND	= 0x1000000000,
};

typedef	struct s_token_stack
{
	char					*start;
	char					*end;
	enum e_token_type		type;
	struct s_token_stack	*next;
}			t_token_stack;

typedef struct s_here_doc
{
	int		fd[2];
	char	*path;
}			t_here_doc;

typedef struct s_infile
{
	int		fd[2];
	char	*path;
}			t_infile;

typedef struct s_outfile
{
	int		fd[2];
	char	*path;
}			t_outfile;

typedef struct s_command
{
	t_infile	*infile;
	int 		argv;
	char		**argc;
	t_outfile	*outfile;
}			t_command;

typedef struct s_shell
{
	unsigned char	exit_code;
	t_token_stack	*tokens;
	t_command	*commands;
	char			running;
	char			*prompt;
	char			*input;
	char			*line;
	int				argc;
	char			**argv;
	char			**env;
}			t_shell;

/*
Bult in
*/

int		ft_env(int argc, char **argv, char**env);

int		ft_export(t_shell *shell);

int		ft_exit(t_shell *shell);

void	lex(t_shell *shell);

void	ft_free(char **str);

void	ft_free_strs(char **strs);

char	*ft_get_env(t_shell *shell, char *str, int size);

bool	syntax_valid(char *input);

int		expand(t_shell *shell);

/*
	token.c
*/

void	append_token(t_shell *shell, t_token_stack *token);

to_token_stack	*get_next_token(to_token_stack *token, e_token_type type);

void	free_token_stack(t_shell *shell);

/*
	tokenizer.c
*/

int		tokenize(t_shell *shell);

#endif
