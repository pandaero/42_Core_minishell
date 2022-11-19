/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:34:20 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/19 15:24:46 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function searches for executable command under path folders.
static int	ispathassist(char *cmd, t_minidata *minidata)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (minidata->splitpath[i] != 0)
	{
		temp = ft_strjoin(minidata->splitpath[i], "/");
		temp2 = ft_strjoin(temp, cmd);
		free(minidata->splitpath[i]);
		minidata->splitpath[i] = temp; // cuz later on execution it will be used
		free(temp);
		if (access(temp2, F_OK) == 0)
		{
			if (access(temp2, X_OK) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

//Function determines whether a command is found within the path.
int	is_pathcmd(char *cmd, t_minidata *minidata)
{
	char	*fullpath;
	int		i;

	i = 0;
	while (ft_strncmp(minidata->env[i], "PATH=", 5) != 0)
		i++;
	fullpath = ft_substr(minidata->env[i], 5, ft_strlen(minidata->env[i]));
	minidata->splitpath = ft_split(fullpath, ':');
	free(fullpath);
	if (ispathassist(cmd, minidata) == 1)
		return (1);
	free_split(minidata->splitpath);
	return (0);
}
