/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:21:14 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/28 21:37:34 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function orders the environment variables in alphabetical order and displays.
void	display_env_alph(t_minidata *minidata)
{
	t_envvar	*curr;

	env_list_order(minidata->envlist);
	curr = minidata->envlist->first;
	while (curr != 0)
	{
		ft_printf("%s\n", curr->whole);
		curr = curr->next;
	}
}

//Function writes to the current shell environment variables.
void	builtin_export(t_minidata *minidata)
{
	char		**splitline;
	char		**splitassign;
	char		*envvar;
	char		*value;

	splitline = ft_split(minidata->currline, ' ');
	if (split_size(splitline) == 2)
	{
		splitassign = ft_split(splitline[1], '=');
		free_split(splitline);
		envvar = ft_strdup(splitassign[0]);
		value = ft_strdup(splitassign[1]);
		free_split(splitassign);
		set_env_var(minidata, envvar, value);
		free(envvar);
		free(value);
	}
	if (split_size(splitline) == 1)
		display_env_alph(minidata);
}
