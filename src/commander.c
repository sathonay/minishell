/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:37:19 by alrey             #+#    #+#             */
/*   Updated: 2025/08/01 22:37:19 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

static void	pipe_it(t_shell *shell)
{
	t_command	*command;
	int			fd[2];

	command = (t_command *) ft_lstlast(shell->command_list)->content;
	if (command->outfile.type != 0)
	{
		ft_lstadd_back(&shell->command_list,
			ft_lstnew(ft_calloc(sizeof(t_command), 1)));
		return ;
	}
	if (pipe(fd))
		return ;
	command->outfile.fd = fd[1];
	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	command = (t_command *) ft_lstlast(shell->command_list)->content;
	command->infile.fd = fd[0];
}

static int	redirect_to_file_flags(t_token_type type)
{
	if (type == HERE_DOC)
		return (O_CREAT | O_RDWR | O_TRUNC);
	if (type == I_FILE)
		return (O_RDONLY);
	if (type == O_FILE)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (type == O_FILE_APPEND)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (0);
}

static t_token_stack	*files_redirect(t_shell *shell, t_token_stack *token)
{
	t_command			*command;
	t_expander_result	expand_res;
	t_redirect			*redir;

	expand_res = expande(shell, get_first_token(token, (STR | QSTR | DQSTR)));
	// TODO check if failed
	command = (t_command *) ft_lstlast(shell->command_list)->content;
	if (command->infile.fd != 0)
		close(command->infile.fd);
	if (token->type & (I_FILE | HERE_DOC))
		redir = &command->infile;
	if (token->type & (O_FILE | O_FILE_APPEND))
		redir = &command->outfile;
	redir->type = token->type;
	if ((redir->type & (I_FILE | O_FILE | O_FILE_APPEND)) > 0)
		redir->path = expand_res.str;
	else if (redir->type == HERE_DOC)
	{
		redir->path = ft_strdup("/tmp/mini_here_doc");
		redir->eof = expand_res.str;
	}
	redir->fd = open(redir->path, redirect_to_file_flags(redir->type), 0777);
	return (expand_res.end);
}

static t_token_stack	*handle_redirections(t_shell *shell,
	t_token_stack *token)
{
	if (token->type == PIPE)
		pipe_it(shell);
	else
		return (files_redirect(shell, token));
	return (token->next);
}

bool	commander(t_shell *shell)
{
	t_command			*command;
	t_token_stack		*token;
	t_expander_result	expand_res;

	token = shell->tokens;
	if (get_first_token(token, 0x3fc))
		ft_lstadd_back(&shell->command_list,
			ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	while (token)
	{
		token = get_first_token(token, 0x3fc);
		if (!token)
			break ;
		if ((token->type & (STR | QSTR | DQSTR)))
		{
			expand_res = expande(shell, token);
			command = (t_command *) ft_lstlast(shell->command_list)->content;
			ft_lstadd_back(&command->argv_builder, ft_lstnew(expand_res.str));
			token = expand_res.end;
		}
		if (token->type & (O_FILE | O_FILE_APPEND | I_FILE | HERE_DOC | PIPE))
			token = handle_redirections(shell, token);
		token = token->next;
	}
	return (1);
}
