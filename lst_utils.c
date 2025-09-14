/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrey <alrey@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 05:42:47 by alrey             #+#    #+#             */
/*   Updated: 2025/09/03 05:48:42 by alrey            ###   ########.fr       */
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

/*static void *lst_previous(t_list *list, t_list *node)
{
  // Unstatic
  while (list->next && list->next != node)
      list = list->next;
  return (list);
}*/
