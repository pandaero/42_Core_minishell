/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:52:27 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/19 15:32:18 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int	prepare_executor(t_minidata *minidata)
{
	if (minidata->num_pipes == 0)
		single_cmd(minidata->simple_cmds, minidata);
	else
	{
		minidata->pid = ft_calloc(sizeof(int), minidata->num_pipes + 2);
		if (!minidata->pid)
			return (allerrors(1, minidata));
		start_executor(minidata);
	}
	return (EXIT_SUCCESS);
}
