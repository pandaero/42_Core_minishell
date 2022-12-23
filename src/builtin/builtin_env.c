/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:01 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/21 16:56:24 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function prints out the environment variables.
void	builtin_env(t_minidata *minidata)
{
	int			ind;

	ind = 0;
	while (ind <= max_env_index(minidata))
	{
		if (find_env_index(minidata, ind) != minidata->env_list->null)
			ft_printf("%s\n", find_env_index(minidata, ind)->whole);
		else
		{
			ind++;
			continue;
		}
		ind++;
	}
	update_return(minidata, EXIT_SUCCESS);
}
