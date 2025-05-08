/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:56 by alrey             #+#    #+#             */
/*   Updated: 2025/05/08 14:51:06 by alrey            ###   ########.fr       */
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
	NONE,
	EMPTY,
	STR,
	PIPE,
	HERE_DOC,
	I_FILE,
	O_FILE,
	O_FILE_APPEND,
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


typedef struct s_command_stack
{
	t_here_doc	*here_doc;
	t_infile	*infile;
}			t_command_stack;

typedef struct s_shell
{
	unsigned char	exit_code;
	t_token_stack	*tokens;
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

int		ft_env(t_shell *shell);

int		ft_export(t_shell *shell);

int		ft_exit(t_shell *shell);

void	lex(t_shell *shell);

void	ft_free(char **str);

void	ft_free_strs(char **strs);

char	*ft_get_env(t_shell *shell, char *str, int size);

bool	syntax_valid(char *input);

int expand(t_shell *shell);

#endif
