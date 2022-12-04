/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:05:08 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/04 19:17:05 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

static char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_envp(t_minidata *minidata)
{
	char	*path_from_envp;
	int		i;
	char	*temp;

	path_from_envp = find_path(minidata->env);
	minidata->splitpath = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (minidata->splitpath[i])
	{
		if (ft_strncmp(&minidata->splitpath[i][ft_strlen(minidata->splitpath[i]) - 1],
			"/", 1) != 0)
		{
			temp = ft_strjoin(minidata->splitpath[i], "/");
			free(minidata->splitpath[i]);
			minidata->splitpath[i] = temp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}