/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:16:56 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 15:10:15 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function performs the clearing of memory that takes place every loop.
void	loop_reset(t_minidata *minidata)
{
	free(minidata->currline);
	if (minidata->pid)
		free(minidata->pid);
	free_split(minidata->splitpath);
}
