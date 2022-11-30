/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:21:14 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/28 22:23:10 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function orders the environment variables in alphabetical order and displays.
static void	display_env_alph(t_minidata *minidata)
{
	t_envvar	*curr;

	env_list_order(minidata->envlist);
	curr = minidata->envlist->first;
	while (curr != 0)
	{
		ft_printf("declare -x %s=\"%s\"\n", curr->var, curr->value);
		curr = curr->next;
	}
}

//Function works out the value of a variable (performs expansion).
static char	*expandedvalue(t_minidata *minidata, char *valuepre)
{
	char	*value;

	value = var_expansion(minidata, valuepre);
	return (value);
}

//Function writes to the current shell environment variables.
void	builtin_export(t_minidata *minidata)
{
	char		**splitline;
	char		**splitassign;
	char		*envvar;
	char		*value;
	int			args;

	splitline = ft_split(minidata->currline, ' ');
	args = split_size(splitline);
	if (args == 2)
	{
		splitassign = ft_split(splitline[1], '=');
		free_split(splitline);
		envvar = ft_strdup(splitassign[0]);
		value = expandedvalue(minidata, splitassign[1]);
		free_split(splitassign);
		set_env_var(minidata, envvar, value);
		free(envvar);
		free(value);
	}
	if (args == 1)
		display_env_alph(minidata);
}
