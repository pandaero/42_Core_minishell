/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:15:34 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/29 11:02:33 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

//Function prints out an error message for when the home variable is not set.
static void	error_cd_home(t_minidata *minidata)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	update_return(minidata, 2);
}

//Function prints out the error message corresponding to chdir not working.
void	chdirerror(t_minidata *minidata)
{
	perror("minishell: ");
	update_return(minidata, EXIT_FAILURE);
}

//Function changes the environment variables to implement a change of directory.
void	cd(t_minidata *minidata, char *dirstr)
{
	char	*temp;
	char	*dirwd;

	dirwd = (char *)malloc(500 * sizeof(char));
	if (chdir(dirstr) == -1)
		chdirerror(minidata);
	else
	{
		if (getcwd(dirwd, 500) == 0)
		{
			free(dirwd);
			chdirerror(minidata);
		}
		else
		{
			temp = ft_strdup(find_env_var_list(minidata, "PWD")->value);
			set_env_var(minidata, "PWD", dirwd);
			set_env_var(minidata, "OLDPWD", temp);
			free(temp);
			free(dirwd);
			update_return(minidata, EXIT_SUCCESS);
		}
	}
}

//Function changes the current directory to home. (default no-arg cd)
static void	cd_home(t_minidata *minidata)
{
	t_envvar	*home;

	home = find_env_var_list(minidata, "HOME");
	if (home == minidata->env_list->null)
	{
		error_cd_home(minidata);
		return ;
	}
	cd(minidata, home->value);
}

//Function changes the current directory where the shell is performing actions.
void	builtin_cd(t_minidata *minidata)
{
	if (split_size(minidata->simple_cmds->str) == 2)
		cd(minidata, minidata->simple_cmds->str[1]);
	if (split_size(minidata->simple_cmds->str) == 1)
		cd_home(minidata);
}
