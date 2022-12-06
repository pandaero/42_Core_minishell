/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:19:08 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/05 21:45:47 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

t_word	*lexerclear_one(t_word **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	lexerdel_first(t_word **lst)
{
	t_word	*node;

	node = *lst;
	*lst = node->next;
	lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

//Function deletes a node in the lexer list according to its i value.
void	lexerdelone(t_word **lst, int key)
{
	t_word	*node;
	t_word	*prev;
	t_word	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		lexerdel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	lexerclear_one(&node);
	*lst = start;
}
