/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:43:48 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 16:43:54 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Function checks that an input line contains valid instructions
int	validline(const char *line, t_minidata *minidata)
{
	char	*cmd;
	int		i;

	cmd = findcommand(line);
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
	if (is_pathcmd(cmd, minidata->env) == 1)
		return (1);
	return (0);
}
