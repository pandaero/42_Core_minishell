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

static int	check_var_name(char *splitassign)
{
	int	i;

	i = 0;
	if (!ft_isalpha(splitassign[0]) && splitassign[0] != '_')
		return (EXIT_FAILURE);
	while (splitassign[i])
	{
		if (ft_isalnum(splitassign[i]) || splitassign[i] == '_')
			i++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	free_staff(char **splitassign, char *value)
{
	free(splitassign[0]);
	free(splitassign);
	free(value);
}

static void	error_var(char **splitassign, char *value, t_minidata *minidata)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putstr_fd(&splitassign[0][0], 2);
	ft_putstr_fd("\n", 2);
	update_return(minidata, 1);
	free_staff(splitassign, value);
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
		value = check_value(splitassign, minidata);
		if (check_var_name(splitassign[0]))
		{
			error_var(splitassign, value, minidata);
			return ;
		}
		set_env_var(minidata, envvar, value);
		free(envvar);
		free_staff(splitassign, value);
	}
	if (args == 1)
		display_env_alph(minidata);
	update_return(minidata, EXIT_SUCCESS);
}
