/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:22:12 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/04 16:58:46 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "stdlib.h"

t_simple_cmds	*simple_cmdnew(char **str, int num_elm, \
								int num_red, t_word *red)
{
	t_simple_cmds	*new_elem;

	new_elem = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_elem)
		return (0);
	new_elem->str = str;
	new_elem->hd_file_name = NULL;
	new_elem->num_redirections = num_red;
	new_elem->num_elements = num_elm;
	new_elem->redirections = red;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

void	simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new)
{
	t_simple_cmds	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*temp;
	t_word			*redirections_temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		redirections_temp = (*lst)->redirections;
		lexerclear(&redirections_temp);
		// if ((*lst)->str)
		// 	free_split((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

t_simple_cmds	*simple_cmdsfirst(t_simple_cmds *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}
