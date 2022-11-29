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
t_envvar	*env_var_cpy(t_envvar *var)
{
	t_envvar	*new;

	new = new_env_var();
	new->index = var->index;
	new->var = ft_strdup(var->var);
	new->value = ft_strdup(var->value);
	new->whole = ft_strdup(var->whole);
	if (var->prev != 0)
		new->prev = var->prev;
	if (var->next != 0)
		new->next = var->next;
	return (new);
}

//Function adds the data from the environment vector element to the envvar node.
void	get_env_var_data(char *env_el, t_envvar *node)
{
	char	**split;

	split = ft_split(env_el, '=');
	node->var = ft_strdup(split[0]);
	if (split[1] != 0)
		node->value = ft_strdup(split[1]);
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
		get_env_var_data(env[i], new);
		add_env_var(envlist, new);
		i++;
	}
}

//Function removes a node from an environment variable linked list.
void	rem_env_var(t_env *envlist, t_envvar *envvar)
{
	if (envvar == 0)
		return ;
	if (envvar->prev == 0)
		envlist->first = envvar->next;
	else
		envvar->prev->next = envvar->next;
	if (envvar->next == 0)
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
		envvar->prev = 0;
		envvar->next = 0;
		envlist->first = envvar;
	}
	else
	{
		envvar->prev = envlist->last;
		envvar->next = 0;
		envlist->last->next = envvar;
	}
	envvar->index = envlist->size;
	envlist->last = envvar;
	envlist->size++;
}
