/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:34:20 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 16:14:11 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function searches for executable command under path folders.
static int	ispathassist(char *cmd, char **splitpath)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	while (splitpath[i] != 0)
	{
		temp = ft_strjoin(splitpath[i], "/");
		temp2 = ft_strjoin(temp, cmd);
		free(temp);
		free(splitpath[i]);
		splitpath[i] = temp2;
		if (access(splitpath[i], F_OK) == 0)
		{
			if (access(splitpath[i], X_OK) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

//Function determines whether a command is found within the path.
int	is_pathcmd(char *cmd, char **env)
{
	char	*fullpath;
	char	**splitpath;
	int		i;

	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	fullpath = ft_substr(env[i], 5, ft_strlen(env[i]));
	splitpath = ft_split(fullpath, ':');
	free(fullpath);
	if (ispathassist(cmd, splitpath) == 1)
		return (1);
	free_split(splitpath);
	return (0);
}
