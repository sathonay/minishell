/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:56 by alrey             #+#    #+#             */
/*   Updated: 2025/04/11 06:06:30 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	running;
	char	*prompt;
	char	**env;
	char	*input;
}			t_shell;

/*
Bult in
*/

int	ft_env(t_shell *shell);

int	ft_export(t_shell *shell);

int	ft_exit(t_shell *shell);

void lex(t_shell *shell);

void ft_free(char **str);

void ft_free_strs(char **strs);

#endif
