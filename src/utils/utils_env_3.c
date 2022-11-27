/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:17:28 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/27 01:19:24 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function determines whether the environment variable list is ordered.
int	is_env_list_ordered(t_env *list)
{
	t_envvar	*curr;

	curr = list->first;
	while (curr != 0)
	{
		if (curr->next == 0)
			break ;
		if (ft_strcmp(curr->var, curr->next->var) > 0)
			return (0);
		curr = curr->next;
	}
	return (1);
}

//Function swaps two nodes in the environment variable list.
void	env_var_swap(t_envvar *var1, t_envvar *var2, t_env *list)
{
	t_envvar	*temp;

	temp = env_var_cpy(var1);
	if (var1->prev != 0)
		var1->prev->next = var2;
	else
		list->first = var2;
	var1->prev = var2;
	var1->next = var2->next;
	if (var2->next != 0)
		var2->next->prev = var1;
	else
		list->last = var1;
	var2->prev = temp->prev;
	var2->next = var1;
	free(temp->var);
	free(temp->value);
	free(temp->whole);
	free(temp);
}

//Function orders the environment variable list alphabetically.
void	env_list_order(t_env *list)
{
	t_envvar	*curr;

	while (is_env_list_ordered(list) == 0)
	{
		curr = list->first;
		while (curr != 0)
		{
			if (curr->next == 0)
				break ;
			if (ft_strcmp(curr->var, curr->next->var) > 0)
				env_var_swap(curr, curr->next, list);
			else
				curr = curr->next;
		}
	}
}

//Function looks for an environment variable in the linked list.
t_envvar	*find_env_var_list(t_minidata *minidata, char *var)
{
	t_envvar	*node;
	int			i;

	node = minidata->envlist->first;
	i = 0;
	while (i <= minidata->envlist->size)
	{
		if (ft_strcmp(node->var, var) == 0)
			return (node);
		node = node->next;
		i++;
	}
	return (0);
}

//Function sets an environment variable's value in the env variable list.
void	set_env_var(t_minidata *minidata, char *var, char *value)
{
	char		*declaration;
	char		*whole;
	t_envvar	*curr;

	declaration = ft_strjoin(var, "=");
	whole = ft_strjoin(declaration, value);
	free(declaration);
	curr = find_env_var_list(minidata, var);
	if (curr == 0)
	{
		curr = new_env_var();
		curr->whole = ft_strdup(whole);
		curr->var = ft_strdup(var);
		curr->value = ft_strdup(value);
		add_env_var(minidata->envlist, curr);
	}
	else
	{
		free(curr->value);
		curr->value = ft_strdup(value);
		curr->whole = ft_strdup(whole);
	}
	free(whole);
}
