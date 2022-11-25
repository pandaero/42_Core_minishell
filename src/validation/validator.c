/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:43:48 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 20:14:53 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function checks that an input line contains valid instructions
int	is_validline(t_minidata *minidata)
{
	char	*cmd;
	int		i;

	cmd = findcommand(minidata->currline);
	i = 0;
	while (minidata->builtincmds[i] != 0)
	{
		if (ft_strlen(cmd) == ft_strlen(minidata->builtincmds[i]))
		{
			if (ft_strncmp(cmd, minidata->builtincmds[i], ft_strlen(cmd)) == 0)
			{
				free(cmd);
				return (1);
			}
		}
		i++;
	}
	i = 0;
	if (is_pathcmd(cmd, minidata) == 1)
	{
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}
