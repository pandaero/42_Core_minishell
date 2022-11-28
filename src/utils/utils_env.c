/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:04:58 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/26 19:59:21 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function finds the pointer to the environment variable from the vector.
char	*find_env_var(char **env, char *var)
{
	int		i;
	char	*tempsearch;

	tempsearch = ft_strjoin(var, "=");
	i = 0;
	while (ft_strncmp(env[i], tempsearch, ft_strlen(tempsearch)) != 0)
		i++;
	free(tempsearch);
	return (env[i]);
}

//Function finds the pointer to the environment variable from the list.
int	ind_env_var_indx(char **env, char *var)
{
	int		i;
	char	*tempsearch;

	tempsearch = ft_strjoin(var, "=");
	i = 0;
	while (ft_strncmp(env[i], tempsearch, ft_strlen(tempsearch)) != 0)
		i++;
	free(tempsearch);
	return (i);
}

//Function gets an environment variable's value from the environment vector.
char	*get_env_var(char **env, char *var)
{
	int		i;
	char	**split;
	char	*tempsearch;

	tempsearch = ft_strjoin(var, "=");
	i = 0;
	while (ft_strncmp(env[i], tempsearch, ft_strlen(tempsearch)) != 0)
	{
		if (i == nonsplit_size(env))
			return (NULL);
		i++;
	}
	free(tempsearch);
	split = ft_split(env[i], '=');
	var = split[1];
	free_split(split);
	return (var);
}

//Function gets the current working directory from the environment vector.
char	*get_cwd(char **env)
{
	int		i;
	char	**split;
	char	*pwd;

	i = 0;
	while (ft_strncmp(env[i], "PWD=", 4) != 0)
	{
		if (i == nonsplit_size(env))
			return (NULL);
		i++;
	}
	split = ft_split(env[i], '=');
	pwd = ft_strdup(split[1]);
	free_split(split);
	return (pwd);
}
