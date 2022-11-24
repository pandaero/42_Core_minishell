/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:39:06 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 15:20:40 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function exits the program cleanly.
void	builtin_exit(t_minidata *minidata)
{
	free_split(minidata->builtincmds);
	free(minidata->currline);
	free(minidata);
	exit(EXIT_SUCCESS);
}
