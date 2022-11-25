/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:01 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/25 14:49:37 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function prints out the environment variables.
void	builtin_env(t_minidata *minidata)
{
	int	i;

	i = 0;
	while (minidata->env[i])
	{
		ft_printf("%s\n", minidata->env[i]);
		i++;
	}
}
