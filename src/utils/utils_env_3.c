/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:17:28 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/23 13:08:47 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function determines whether the environment variable list is ordered.
int	is_env_list_ordered(t_env *list)
{
	t_envvar	*curr;

	curr = list->first;
	while (curr != list->null)
	{
		if (curr->next == list->null)
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

	temp = env_var_cpy(list, var1);
	if (var1->prev != list->null && var1->prev != NULL)
		var1->prev->next = var2;
	else
		list->first = var2;
	var1->prev = var2;
	var1->next = var2->next;
	if (var2->next != list->null)
		var2->next->prev = var1;
	else
		list->last = var1;
	var2->prev = temp->prev;
	var2->next = var1;
	free(temp->var);
	if (temp->value != list->null->value)
		free(temp->value);
	if (temp->whole != list->null->whole)
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
		while (curr != list->null)
		{
			if (curr->next == list->null)
				break ;
			if (ft_strcmp(curr->var, curr->next->var) > 0)
				env_var_swap(curr, curr->next, list);
			else
				curr = curr->next;
		}
	}
}

static void	check_path(char *var, t_minidata *minidata)
{
	if (ft_strncmp(var, "PATH", 5) == 0)
		working_path(minidata);
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
	if (curr == minidata->env_list->null)
	{
		curr = new_env_var();
		curr->whole = ft_strdup(whole);
		curr->var = ft_strdup(var);
		curr->value = ft_strdup(value);
		add_env_var(minidata->env_list, curr);
	}
	else
	{
		free(curr->value);
		curr->value = ft_strdup(value);
		free(curr->whole);
		curr->whole = ft_strdup(whole);
	}
	free(whole);
	check_path(var, minidata);
}
