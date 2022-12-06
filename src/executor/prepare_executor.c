/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:09:30 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/06 19:51:46 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	single_cmd(t_minidata *minidata)
{
	int	fd_in;
	int	end[2];

	end[0] = 0;
	end[1] = 0;
	fd_in = STDIN_FILENO;
	if (is_builtincmd(minidata->simple_cmds->str[0]) > 0)
		builtin_execution(minidata, \
							is_builtincmd(minidata->simple_cmds->str[0]));
	else
	{
		forking(minidata, end, fd_in, minidata->simple_cmds);
	}
}

int	prepare_executor(t_minidata *minidata)
{
	if (minidata->num_pipes == 0)
	{
		minidata->pid = ft_calloc(2, sizeof(int));
	 	single_cmd(minidata);
	}
	else
	{
		minidata->pid = ft_calloc(sizeof(int), minidata->num_pipes + 2);
		if (!minidata->pid)
			return (allerrors(1, minidata));
		start_executor(minidata);
	}
	return (EXIT_SUCCESS);
}
