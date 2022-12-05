/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:01 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 20:48:45 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function prints out the environment variables.
void	builtin_env(t_minidata *minidata)
{
	t_envvar	*curr;
	int			ind;

	ind = 0;
	while (ind < minidata->env_list->size)
	{
		curr = minidata->env_list->first;
		while (curr->index != ind)
		{
			if (curr->next == 0 && curr->index != ind)
			{
				ind++;
				curr = minidata->env_list->first;
				break ;
			}
			curr = curr->next;
		}
		ft_printf("%s\n", curr->whole);
		ind++;
	}
}
