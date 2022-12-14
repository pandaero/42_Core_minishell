/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:17:16 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/29 10:35:48 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function frees a minidata struct.
void	free_minidata(t_minidata *minidata)
{
	free_split(minidata->builtincmds);
	free_split(minidata->splitpath);
	free_env(minidata->env_list);
	free(minidata->last_return);
	free(minidata->currline);
	free(minidata->dollar);
	free(minidata);
}

//Function frees a 2D char array made from ft_split.
void	free_split(char **charr)
{
	int	i;

	i = 0;
	while (charr[i])
	{
		if (charr[i] != NULL)
			free(charr[i]);
		i++;
	}
	free(charr);
}

//Function frees an environment variable linked list.
void	free_env(t_env *list)
{
	while (list->size > 0)
		rem_env_var(list, list->last);
	free(list->null->var);
	free(list->null->value);
	free(list->null->whole);
	free(list->null);
	free(list);
}

//Function frees an entire lexer linked list.
void	free_lexer(t_word **lst)
{
	t_word	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
