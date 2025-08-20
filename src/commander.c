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

void	free_command(t_command *command)
{
	ft_lstclear(&command->argv_builder, free);
	free_str_array(command->argv);
}

static void pipe_it(t_shell *shell)
{
	t_command	*command;
	int			fd[2];
	command = (t_command *) ft_lstlast(shell->command_list)->content;
		
	if (command->outfile.type > 0)
	{
		ft_lstadd_back(&shell->command_list,
			ft_lstnew(ft_calloc(sizeof(t_command), 1)));
		return;
	}
	printf("pipe_it\n");
	if (pipe(fd))
		return ;
	command->outfile.fd = fd[1];
	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	command = (t_command *) ft_lstlast(shell->command_list)->content;
	command->infile.fd = fd[0];
}
 // TODO: MOVE START TO UTILS FILES
static size_t	ullen(unsigned long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n / 10 > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}


static char	*ft_ptoa(size_t n)
{
	size_t	strlen;
	char	*str;

	strlen = ullen(n);
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	str[strlen] = '\0';
	while (n / 10 != 0)
	{
		str[--strlen] = '0' + (n % 10);
		n /= 10;
	}
	str[--strlen] = '0' + (n % 10);
	return (str);
}
// MOVE END

static t_token_stack *infiles_redirect(t_shell *shell, t_token_stack *token)
{
	t_command	*command;
	t_expander_result expand_res;
	t_redirect *redirect;
	token = get_first_token(token, (STR | QSTR | DQSTR));
	expand_res = expande(shell, token);
	command = (t_command *) ft_lstlast(shell->command_list)->content;
	if (token->type & (I_FILE | HERE_DOC))
		redirect = &command->infile;
	if (token->type & (O_FILE | O_FILE_APPEND))
		redirect = &command->outfile;
	if ((redirect->type & (I_FILE | O_FILE | O_FILE_APPEND)) > 0)
		redirect->path = expand_res.str;
	else if (redirect->type == HERE_DOC)
		redirect->path = ft_ptoa((unsigned long) redirect);
	if (token->type == HERE_DOC)
		redirect->fd = open(redirect->path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (token->type == I_FILE)
		redirect->fd = open(redirect->path, O_RDONLY, 0777);
	if (token->type == O_FILE)
		redirect->fd = open(redirect->path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (token->type == O_FILE_APPEND)
		redirect->fd = open(redirect->path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	redirect->type = token->type;
	return (expand_res.end);
}

static t_token_stack	*handle_redirections(t_shell *shell, t_token_stack *token)
{
	printf("handle redirect\n");
	if (token->type == PIPE)
		pipe_it(shell);
	else
		return (infiles_redirect(shell, token));
	return (token->next);
}

bool	commander(t_shell *shell)
{
	t_token_stack	*token;
	t_expander_result expand_res;

	ft_lstadd_back(&shell->command_list,
		ft_lstnew(ft_calloc(sizeof(t_command), 1)));
	token = shell->tokens;
	while (token)
	{
		token = get_first_token(token, 0x3fc);
		if (!token)
			break ;
		if (token->type & (O_FILE | O_FILE_APPEND | I_FILE | HERE_DOC | PIPE))
			token = handle_redirections(shell, token);
		printf("token %p %s\n", token, get_token_str_type(token->type));
		if ((token->type & (STR | QSTR | DQSTR)))
		{
			expand_res = expande(shell, token);
			ft_lstadd_back(&((t_command *) ft_lstlast(shell->command_list))
				->argv_builder, ft_lstnew(expand_res.str));
			token = expand_res.end;
		}
		token = token->next;
	}
	return (1);
}
