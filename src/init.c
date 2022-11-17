/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:08:30 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 15:17:59 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//Function initialises the minidata.
void	init_minidata(t_minidata *minidata)
{
	char	*builtin;

	builtin = ft_strdup("echo.cd.pwd.export.unset.env.exit");
	minidata->builtincmds = ft_split(builtin, '.');
	free(builtin);
}
