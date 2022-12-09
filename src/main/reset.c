/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:16:56 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 20:42:36 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function performs the clearing of memory that takes place every loop.
void	loop_reset(t_minidata *minidata)
{
	// ft_printf("HERE7\n");
	simple_cmdsclear(&minidata->simple_cmds);
	// ft_printf("HERE8\n");
	free(minidata->currline);
	minidata->currline = NULL;
	// ft_printf("HERE9\n");
	if (minidata->pid)
		free(minidata->pid);
	// ft_printf("HERE9.5\n");
	// ft_printf("SSSSSSSS\n");
	if (minidata->splitpath)
	{
		free_split(minidata->splitpath); // need to get path in each iteration 
	}
	// ft_printf("HERE10\n");
	minidata->reset = true;
	minidata->simple_cmds = NULL;
	minidata->lexer_list = NULL;
	minidata->splitpath = NULL;
	minidata->heredoc = false;
	minidata->stop_heredoc = 0;
	minidata->in_heredoc= 0;
	working_path(minidata);
}
