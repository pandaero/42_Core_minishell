/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:21:14 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/14 17:01:28 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function orders the environment variables in alphabetical order and displays.
static void	display_env_alph(t_minidata *minidata)
{
	t_envvar	*curr;

	env_list_order(minidata->env_list);
	curr = minidata->env_list->first;
	while (curr != minidata->env_list->null)
	{
		ft_printf("declare -x %s=\"%s\"\n", curr->var, curr->value);
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
	int			args;

	splitline = minidata->simple_cmds->str;
	args = split_size(splitline);
	if (args == 2)
	{
		splitassign = ft_split(splitline[1], '=');
		envvar = ft_strdup(splitassign[0]);
		value = string_expansion(minidata, splitassign[1]);
		free(splitassign[0]);
		free(splitassign);
		set_env_var(minidata, envvar, value);
		free(envvar);
		free(value);
	}
	if (args == 1)
		display_env_alph(minidata);
	update_return(minidata, EXIT_SUCCESS);
}
