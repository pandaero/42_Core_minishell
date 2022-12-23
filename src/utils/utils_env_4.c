/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:45:52 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/23 13:29:30 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function appends a forward slash to the PATH elements to create splitpath.
void	working_path(t_minidata *minidata)
{
	int		i;
	int		len;
	char	*temp;
	char	*pathvalue;

	pathvalue = ft_strdup(find_env_var_list(minidata, "PATH")->value);
	minidata->splitpath = ft_split(pathvalue, ':');
	free(pathvalue);
	len = 0;
	i = 0;
	while (minidata->splitpath[i])
	{
		len = ft_strlen(minidata->splitpath[i]);
		if (ft_strncmp(&minidata->splitpath[i][len - 1], "/", 1) != 0)
		{
			temp = ft_strjoin(minidata->splitpath[i], "/");
			free(minidata->splitpath[i]);
			minidata->splitpath[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

//Function finds the highest index present in the environment variable list.
int	max_env_index(t_minidata *minidata)
{
	int			max;
	t_envvar	*curr;

	max = 0;
	curr = minidata->env_list->first;
	while (curr != minidata->env_list->null)
	{
		if (curr->index > max)
			max = curr->index;
		curr = curr->next;
	}
	return (max);
}

//Function finds an environment variable according to its index in the list.
t_envvar	*find_env_index(t_minidata *minidata, int ind)
{
	t_envvar	*curr;

	curr = minidata->env_list->first;
	while (curr != minidata->env_list->null)
	{
		if (curr->index == ind)
			return (curr);
		curr = curr->next;
	}
	return (minidata->env_list->null);
}

//Function looks for an environment variable in the linked list.
t_envvar	*find_env_var_list(t_minidata *minidata, char *var)
{
	t_envvar	*node;

	node = minidata->env_list->first;
	while (node != minidata->env_list->null)
	{
		if (ft_strcmp(node->var, var) == 0)
			return (node);
		node = node->next;
	}
	return (minidata->env_list->null);
}
