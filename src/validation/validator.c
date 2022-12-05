/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:43:48 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/04 17:37:34 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function checks that an input command line contains executable commands.
int	is_validcmdline(t_minidata *minidata)
{
	char	*cmd;
	int		i;
	
	cmd = minidata->simple_cmds->str[0];
	i = 0;
	while (minidata->builtincmds[i] != 0)
	{
		if (ft_strlen(cmd) == ft_strlen(minidata->builtincmds[i]))
		{
			if (ft_strncmp(cmd, minidata->builtincmds[i], ft_strlen(cmd)) == 0)
				return (1);
		}
		i++;
	}
	i = 0;
	if (is_pathcmd(cmd, minidata) == 1)
		return (1);
	return (0);
}
