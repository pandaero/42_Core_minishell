/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:24:26 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/29 08:30:35 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function clears the contents of a local environment variable.
void	builtin_unset(t_minidata *minidata)
{
	t_envvar	*var;
	char		**splitline;
	char		*search;
	int			i;

	i = 1;
	splitline = minidata->simple_cmds->str;
	while (splitline[i])
	{
		search = ft_strdup(splitline[i]);
		var = find_env_var_list(minidata, search);
		if (var != minidata->env_list->null)
			rem_env_var(minidata->env_list, var);
		free(search);
		i++;
		update_return(minidata, EXIT_SUCCESS);
	}
}
