/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:24:26 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/20 17:08:30 by pandalaf         ###   ########.fr       */
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

	splitline = minidata->simple_cmds->str;
	search = ft_strdup(splitline[1]);
	var = find_env_var_list(minidata, search);
	if (var != minidata->env_list->null)
		rem_env_var(minidata->env_list, var);
	free(search);
	update_return(minidata, EXIT_SUCCESS);
}
