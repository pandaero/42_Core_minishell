/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:06 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/20 03:05:48 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Function adds a new node to the end of the list.
void	list_add_end(t_dlist *list, t_base *new)
{
	t_base	*temp;

	if (list->start == 0)
	{
		list->start = new;
		list->end = new;
	}
	else
	{
		temp = list->start;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = new;
		list->end = new;
		new->prev = temp;
	}
}
