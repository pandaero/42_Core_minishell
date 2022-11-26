/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:17:16 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/26 03:19:57 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function frees a minidata struct.
void	free_minidata(t_minidata *minidata)
{
	free_split(minidata->builtincmds);
	free(minidata->currline);
	free(minidata);
}

//Function frees a 2D char array made from ft_split.
void	free_split(char **charr)
{
	int	i;

	i = 0;
	while (charr[i] != 0)
	{
		free(charr[i]);
		i++;
	}
	free(charr);
}

//Function frees an environment variable linked list.
void	free_env(t_env *list)
{
	while (list->size > 0)
		rem_env_var(list, list->last);
	free(list);
}
