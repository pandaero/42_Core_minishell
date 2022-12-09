/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:08:57 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 22:16:41 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function determines whether a command line calls a built-in command.
int	is_builtincmd(char	*cmd)
{
	if (ft_strncmp("exit", cmd, 5) == 0)
		return (1);
	if (ft_strncmp("pwd", cmd, 4) == 0)
		return (2);
	if (ft_strncmp("export", cmd, 7) == 0)
		return (3);
	if (ft_strncmp("unset", cmd, 6) == 0)
		return (4);
	if (ft_strncmp("env", cmd, 4) == 0)
		return (5);
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (6);
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (7);
	return (0);
}

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
