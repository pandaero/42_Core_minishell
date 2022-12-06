/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:08:57 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 19:05:12 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function handles the execution of built-in commands.
void	builtin_execution(t_minidata *minidata, int builtin)
{
	if (builtin == 1)
		builtin_exit(minidata);
	if (builtin == 2)
		builtin_pwd(minidata);
	if (builtin == 3)
		builtin_export(minidata);
	if (builtin == 4)
		builtin_unset(minidata);
	if (builtin == 5)
		builtin_env(minidata);
	if (builtin == 6)
		builtin_cd(minidata);
	if (builtin == 7)
		builtin_echo(minidata);
}
