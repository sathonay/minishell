/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:42:47 by alrey             #+#    #+#             */
/*   Updated: 2025/09/15 08:00:25 by alrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	**lst_to_array(t_list *lst)
{
	size_t	index;
	void	**array;

	index = 0;
	array = ft_calloc(ft_lstsize(lst) + 1, sizeof(void *));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[index] = lst->content;
		index++;
		lst = lst->next;
	}
	return (array);
}

int	ft_lstappend_cstruct(t_list **lst, size_t struct_size)
{
	void	*struct_ptr;
	t_list	*node_ptr;

	struct_ptr = ft_calloc(struct_size, 1);
	if (!struct_ptr)
		return (0);
	node_ptr = ft_lstnew(struct_ptr);
	if (!node_ptr)
	{
		free(struct_ptr);
		return (0);
	}
	ft_lstadd_back(lst, node_ptr);
	return (1);
}

/*static void *lst_previous(t_list *list, t_list *node)
{
  // Unstatic
  while (list->next && list->next != node)
      list = list->next;
  return (list);
}*/
