/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:01 by alrey             #+#    #+#             */
/*   Updated: 2024/11/07 16:36:45 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
