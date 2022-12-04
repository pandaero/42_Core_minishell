/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:09:30 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/04 23:47:26 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	prepare_executor(t_minidata *minidata)
{
	// if (minidata->num_pipes == 0)
	// 	single_cmd(minidata->simple_cmds, minidata);
	// else
	// {
	minidata->pid = ft_calloc(sizeof(int), minidata->num_pipes + 2);
	if (!minidata->pid)
		return (allerrors(1, minidata));
	start_executor(minidata);
	// }
	return (EXIT_SUCCESS);
}
