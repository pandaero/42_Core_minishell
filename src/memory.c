/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:17:16 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 15:21:45 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//Function frees a minidata struct.
void	free_minidata(t_minidata *minidata)
{
	int	i;

	i = 0;
	while (minidata->builtincmds[i])
	{
		free(minidata->builtincmds[i]);
		i++;
	}
	free(minidata->builtincmds[i]);
	free(minidata->builtincmds);
}
