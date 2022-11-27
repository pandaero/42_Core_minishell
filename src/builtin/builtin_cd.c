/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:15:34 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/27 00:54:42 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

//Function prints out an error message for when the home variable is not set.
void	error_cd_home(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
}

//Function changes the environment variables to implement a change of directory.
void	cd(t_minidata *minidata, char *dir)
{
	char	*temp;

	if (chdir(dir) == -1)
		ft_putstr_fd("chdir error\n", STDERR);
	else
	{
		temp = ft_strdup(find_env_var_list(minidata, "PWD")->value);
		set_env_var(minidata, "PWD", dir);
		set_env_var(minidata, "OLDPWD", temp);
		free(temp);
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
