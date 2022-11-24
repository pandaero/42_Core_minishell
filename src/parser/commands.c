/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:34:20 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 15:52:18 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
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
		if (access(temp2, F_OK) == 0)
		{
			if (access(temp2, X_OK) == 0)
			{
				free(temp2);
				return (1);
			}
		}
		free(temp2);
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

//Function is a shortcut to free a pointer with given return value.
static int	freewithreturn(char *ptr, int ret)
{
	free(ptr);
	return (ret);
}

//Function determines whether a command line calls a built-in command.
int	is_builtincmd(t_minidata *minidata)
{
	char	*cmd;

	cmd = findcommand(minidata->currline);
	if (ft_strncmp("exit", cmd, 4) == 0 && ft_strlen(cmd) == 4)
		return (freewithreturn(cmd, 1));
	if (ft_strncmp("pwd", cmd, 3) == 0 && ft_strlen(cmd) == 3)
		return (freewithreturn(cmd, 2));
	if (ft_strncmp("export", cmd, 6) == 0 && ft_strlen(cmd) == 6)
		return (freewithreturn(cmd, 3));
	if (ft_strncmp("unset", cmd, 5) == 0 && ft_strlen(cmd) == 5)
		return (freewithreturn(cmd, 4));
	if (ft_strncmp("env", cmd, 3) == 0 && ft_strlen(cmd) == 3)
		return (freewithreturn(cmd, 5));
	if (ft_strncmp("cd", cmd, 2) == 0 && ft_strlen(cmd) == 2)
		return (freewithreturn(cmd, 6));
	if (ft_strncmp("echo", cmd, 4) == 0 && ft_strlen(cmd) == 4)
		return (freewithreturn(cmd, 7));
	return (freewithreturn(cmd, 0));
}
