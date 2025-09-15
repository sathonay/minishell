/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:37:19 by alrey             #+#    #+#             */
/*   Updated: 2025/09/09 16:32:02 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

static void	pipe_it(t_shell *shell, int *pips)
{
	if (pipe(pips))
	{
		printf("el minishello: %s\n",
			strerror(errno));
		errno = 0;
		if (!ft_lstappend_cstruct(&shell->command_list, sizeof(t_command)))
		{
			printf("NEM: failed to allocate command struct\n");
			return ;
		}
		pips[1] = -1;
		pips[0] = -1;
		return ;
	}
	if (!ft_lstappend_cstruct(&shell->command_list, sizeof(t_command)))
	{
		printf("NEM: failed to allocate command struct\n");
		(close(pips[0]), close(pips[1]));
		return ;
	}
	ft_memcpy(((t_command *) ft_lstlast(shell->command_list)->content)
		->prev_pipe, pips, sizeof(int) * 2);
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

static t_token_stack	*files_redirect(t_shell *shell, t_redirect *redir,
	t_token_stack *token)
{
	t_expander_result	expand_res;

	expand_res = expande(shell, get_first_token(token, (STR | QSTR | DQSTR)));
	redir->type = token->type;
	if ((redir->type & (I_FILE | O_FILE | O_FILE_APPEND)) > 0)
		redir->path = expand_res.str;
	else if (redir->type == HERE_DOC)
	{
		redir->path = ft_strdup("/tmp/mini_here_doc");
		redir->eof = expand_res.str;
	}
	if (!redir->path)
	{
		printf("el minishello: redirection failed: path null\n");
		redir->fd = -1;
		return (expand_res.end);
	}
	if (redir->type == HERE_DOC)
		return (expand_res.end);
	redir->fd = open(redir->path, redirect_to_file_flags(redir->type), 0777);
	return (expand_res.end);
}

static t_token_stack	*handle_redirections(t_shell *shell,
	t_token_stack *token)
{
	t_command	*cmd;
	t_redirect	*affected_redirect;

	cmd = ft_lstlast(shell->command_list)->content;
	if (token->type == PIPE)
		pipe_it(shell, cmd->next_pipe);
	else
	{
		if (token->type & (I_FILE | HERE_DOC))
			affected_redirect = &cmd->infile;
		if (token->type & (O_FILE | O_FILE_APPEND))
			affected_redirect = &cmd->outfile;
		if (affected_redirect->fd > 0)
			close(affected_redirect->fd);
		free_str(&affected_redirect->path);
		free_str(&affected_redirect->eof);
		token = files_redirect(shell, affected_redirect, token);
		if (errno != 0)
		{
			printf("el minishello: %s: %s\n", strerror(errno),
				affected_redirect->path);
			errno = 0;
		}
	}
	return (token);
}

bool	commander(t_shell *shell)
{
	t_command			*command;
	t_token_stack		*token;
	t_expander_result	expand_res;

	token = shell->tokens;
	if (!get_first_token(token, ALL_NON_EMPTY)
		|| !ft_lstappend_cstruct(&shell->command_list, sizeof(t_command)))
		return (0);
	while (token)
	{
		token = get_first_token(token, ALL_NON_EMPTY);
		if (!token || errno != 0)
			break ;
		if (!errno && (token->type & (STRINGS)))
		{
			expand_res = expande(shell, token);
			command = (t_command *) ft_lstlast(shell->command_list)->content;
			ft_lstadd_back(&command->argv_builder, ft_lstnew(expand_res.str));
			token = expand_res.end;
		}
		if (!errno && token->type & (REDIRECTIONS | PIPE))
			token = handle_redirections(shell, token);
		token = token->next;
	}
	return (errno == 0);
}
