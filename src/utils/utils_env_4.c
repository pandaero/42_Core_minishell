/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:45:52 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 19:32:36 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function appends a forward slash to the PATH elements to create splitpath.
void	working_path(t_minidata *minidata)
{
	int		i;
	int		len;
	char	*temp;
	char	*pathvalue;

	pathvalue = ft_strdup(find_env_var_list(minidata, "PATH")->value);
	minidata->splitpath = ft_split(pathvalue, ':');
	free(pathvalue);
	len = 0;
	i = 0;
	while (minidata->splitpath[i])
	{
		len = ft_strlen(minidata->splitpath[i]);
		if (ft_strncmp(&minidata->splitpath[i][len - 1], "/", 1) != 0)
		{
			temp = ft_strjoin(minidata->splitpath[i], "/");
			free(minidata->splitpath[i]);
			minidata->splitpath[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
