/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:08:57 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/23 20:13:52 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Function handles the execution of built-in commands.
void	builtin_execution(t_minidata *minidata)
{
	if (is_builtincmd(minidata) == 1)
		builtin_exit(minidata);
	if (is_builtincmd(minidata) == 2)
		builtin_pwd(minidata);
	if (is_builtincmd(minidata) == 3)
		builtin_export(minidata);
	if (is_builtincmd(minidata) == 4)
		builtin_unset(minidata);
	if (is_builtincmd(minidata) == 5)
		builtin_env(minidata);
	if (is_builtincmd(minidata) == 6)
		builtin_cd(minidata);
	if (is_builtincmd(minidata) == 7)
		builtin_echo(minidata);
}
