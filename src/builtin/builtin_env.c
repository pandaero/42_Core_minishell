/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:01 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/26 20:15:50 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function prints out the environment variables.
void	builtin_env(t_minidata *minidata)
{
	t_envvar	*curr;
	int			ind;

	ind = 0;
	while (ind < minidata->envlist->size)
	{
		curr = minidata->envlist->first;
		while (curr->index != ind)
			curr = curr->next;
		ft_printf("%s\n", curr->whole);
		ind++;
	}
}
