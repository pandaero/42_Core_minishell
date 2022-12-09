/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:22:12 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/09 18:58:05 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <stdio.h>

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
void	free_split1(char **charr)
{
	int	i;

	i = 0;
	while (charr[i])
	{
		free(charr[i]);
		i++;
	}
	free(charr);
}


void	simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*temp;
	t_word			*redirections_temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		ft_printf("HELLO1\n");
		temp = (*lst)->next;
		redirections_temp = (*lst)->redirections;
		ft_printf("HELLO2\n");
		free_lexer(&redirections_temp);
		ft_printf("HELLO3\n");
		if ((*lst)->str)
		{
			int i = 0;
			while((*lst)->str[i])
			{
				printf("here:%s\n", (*lst)->str[i]);
				i++;
			}
			free_split1((*lst)->str);
			(*lst)->str = NULL;
		}
		if (!(*lst)->str)
			printf("freed:\n");
		else
			printf("not freed: %s\n", (*lst)->str[0]);
		ft_printf("HELLO4\n");
		if ((*lst)->hd_file_name)
		{
			printf("%s\n", (*lst)->hd_file_name);
			free((*lst)->hd_file_name);
		}
		ft_printf("HELLO5\n");
		free(*lst);
		ft_printf("HELLO6\n");
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
