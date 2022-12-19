/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:16:56 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/19 15:30:00 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

void initi_minidata(t_minidata *minidata)
{
	minidata->reset = true;
	minidata->simple_cmds = NULL;
	minidata->lexer_list = NULL;
	minidata->splitpath = NULL;
	minidata->pid = NULL;
	minidata->heredoc = false;
	minidata->stop_heredoc = 0;
	minidata->in_heredoc = 0;
	minidata->currline = NULL;
}

//Function performs the clearing of memory that takes place every loop.
void	loop_reset(t_minidata *minidata)
{
	simple_cmdsclear(&minidata->simple_cmds);
	free(minidata->currline);
	minidata->currline = NULL;
	if (minidata->pid)
		free(minidata->pid);
	if (minidata->splitpath)
		free_split(minidata->splitpath); // need to get path in each iteration 
	initi_minidata(minidata);
	working_path(minidata);
}

void	loop_reset_err(t_minidata *minidata)
{
	simple_cmdsclear(&minidata->simple_cmds);
	free(minidata->currline);
	if (minidata->splitpath)
		free_split(minidata->splitpath); // need to get path in each iteration 
	if (minidata->pid)
		free(minidata->pid);
	initi_minidata(minidata);
	working_path(minidata);
}
