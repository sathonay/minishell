/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:55:41 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 10:55:41 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	stack_args(t_command *command)
{
	errno == 0;
	command->argc = ft_lstsize(command->argv_builder);
	command->argv = (char **) lst_to_array(command->argv_builder);
	if (errno != 0)
		return ;
	ft_lstclear(&command->argv_builder, NULL);
}
