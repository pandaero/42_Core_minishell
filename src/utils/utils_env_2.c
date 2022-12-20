/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:58:30 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/29 03:37:03 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <limits.h>

//Function copies a node element to a new one.
t_envvar	*env_var_cpy(t_env *list, t_envvar *var)
{
	t_envvar	*new;

	new = new_env_var();
	new->index = var->index;
	if (ft_strncmp(var->var, "", 1) != 0)
		new->var = ft_strdup(var->var);
	if (var->value != NULL)
		new->value = ft_strdup(var->value);
	else
		new->value = list->null->value;
	if (ft_strncmp(var->whole, "", 1) != 0)
		new->whole = ft_strdup(var->whole);
	if (var->prev != list->null)
		new->prev = var->prev;
	if (var->next != list->null)
		new->next = var->next;
	return (new);
}

//Function adds the data from the environment vector element to the envvar node.
void	get_env_var_data(char *env_el, t_envvar *node)
{
	char	**split;

	split = ft_split(env_el, '=');
	free(node->var);
	node->var = ft_strdup(split[0]);
	if (split[1] != NULL)
	{
		free(node->value);
		node->value = ft_strdup(split[1]);
	}
	free(node->whole);
	node->whole = ft_strdup(env_el);
	free_split(split);
}

//Function fills the environment variable list from the vector.
void	fill_env(t_env *envlist, char **env)
{
	int			i;
	t_envvar	*new;

	i = 0;
	while (env[i])
	{
		new = new_env_var();
		new->index = i;
		new->prev = envlist->null;
		new->next = envlist->null;
		get_env_var_data(env[i], new);
		add_env_var(envlist, new);
		i++;
	}
	env_list_order(envlist);
}

//Function removes a node from an environment variable linked list.
void	rem_env_var(t_env *envlist, t_envvar *envvar)
{
	if (envvar == envlist->null || envvar == NULL)
		return ;
	if (envvar->prev == envlist->null || envvar->prev == NULL)
		envlist->first = envvar->next;
	else
		envvar->prev->next = envvar->next;
	if (envvar->next == envlist->null || envvar->next == NULL)
		envlist->last = envvar->prev;
	else
		envvar->next->prev = envvar->prev;
	free(envvar->var);
	free(envvar->value);
	free(envvar->whole);
	free(envvar);
	envlist->size--;
}

//Function adds a node to an environment variable linked list.
void	add_env_var(t_env *envlist, t_envvar *envvar)
{
	if (envlist->size == 0)
	{
		envvar->prev = envlist->null;
		envvar->next = envlist->null;
		envlist->first = envvar;
	}
	else
	{
		envvar->prev = envlist->last;
		envvar->next = envlist->null;
		envlist->last->next = envvar;
	}
	envvar->index = envlist->size;
	envlist->last = envvar;
	envlist->size++;
}
