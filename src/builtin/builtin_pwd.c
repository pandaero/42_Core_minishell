/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:58 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 20:29:08 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function prints the current working directory where the shell is acting.
void	builtin_pwd(t_minidata *minidata)
{
	char	*pwd;
	int		i;

	i = 0;
	while (ft_strncmp(minidata->env[i], "PWD=", 4) != 0)
		i++;
	pwd = ft_substr(minidata->env[i], 4, ft_strlen(minidata->env[i]));
	ft_printf("%s\n", pwd);
	free(pwd);
}
