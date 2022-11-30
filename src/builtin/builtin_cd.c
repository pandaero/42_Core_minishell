/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:15:34 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/30 13:41:55 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//Function prints out an error message for when the home variable is not set.
void	error_cd_home(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
}

//Function changes the environment variables to implement a change of directory.
void	cd(t_minidata *minidata, char *dirstr)
{
	char	*temp;
	char	*dirwd;

	dirwd = (char *)malloc(500 * sizeof(char));
	if (chdir(dirstr) == -1)
		perror("minishell: ");
	else
	{
		if (getcwd(dirwd, 500) == 0)
		{
			free(dirwd);
			perror("minishell: ");
		}
		else
		{
			temp = ft_strdup(find_env_var_list(minidata, "PWD")->value);
			set_env_var(minidata, "PWD", dirwd);
			set_env_var(minidata, "OLDPWD", temp);
			free(temp);
			free(dirwd);
		}
	}
}

//Function changed the current directory to home. (default no-arg cd)
static void	cd_home(t_minidata *minidata)
{
	t_envvar	*home;

	home = find_env_var_list(minidata, "HOME");
	if (home == 0)
		error_cd_home();
	cd(minidata, home->value);
}

//Function changes the current directory where the shell is performing actions.
void	builtin_cd(t_minidata *minidata)
{
	char	**splitline;

	splitline = ft_split(minidata->currline, ' ');
	if (split_size(splitline) == 2)
		cd(minidata, var_expansion(minidata, splitline[1]));
	if (split_size(splitline) == 1)
		cd_home(minidata);
	free_split(splitline);
}
