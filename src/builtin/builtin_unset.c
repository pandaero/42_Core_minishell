/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:24:26 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 20:49:14 by pandalaf         ###   ########.fr       */
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

	splitline = ft_split(minidata->currline, ' ');
	search = ft_strdup(splitline[1]);
	free_split(splitline);
	var = find_env_var_list(minidata, search);
	if (var)
		rem_env_var(minidata->env_list, var);
	free(search);
}
