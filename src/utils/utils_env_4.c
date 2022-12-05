/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:45:52 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 19:47:44 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function appends a forward slash to the PATH elements to create splitpath.
void	working_path(t_minidata *minidata)
{
	int		i;
	int		len;
	char	*temp;
	char	*pathvalue;

	pathvalue = find_env_var_list(minidata, "PATH");
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
			minidata->splitpath[i] = temp;
		}
		i++;
	}
}
