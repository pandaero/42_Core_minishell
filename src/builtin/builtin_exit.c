/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:39:06 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/14 16:57:05 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>

//Function writes out the "too many arguments" error to standard error.
static int	error_exit(int err, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (err == 1)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
}

//Function frees elements and exits the program with given number.
static void	free_exit(t_minidata *minidata, char **splitline, int ret)
{
	free_minidata(minidata);
	exit(ret);
}

//Function handles behaviour of exit for normal (not too many args) condition.
static void	exit_normal(t_minidata *minidata, char **splitline, int *exitno)
{
	if (split_size(splitline) == 2 && (ft_atol(splitline[1]) == -1 || \
			is_validnum(splitline[1]) == 0))
			*exitno = error_exit(1, splitline[1]);
	else if (split_size(splitline) == 2)
	{
		if (ft_atol(splitline[1]) > 0)
			*exitno = ft_atol(splitline[1]) % 256;
		else
			*exitno = (ft_atol(splitline[1]) * -1) % 256;
	}
	else
		*exitno = EXIT_SUCCESS;
	free_exit(*exitno, splitline, minidata);
}

//Function exits the program cleanly.
void	builtin_exit(t_minidata *minidata)
{
	char	**splitline;
	int		exitno;
	int		err;

	exitno = 0;
	splitline = minidata->simple_cmds->str;
	if (ft_strncmp(find_env_var_list(minidata, "SHLVL")->value, "1", 2) == 0)
		ft_printf("logout\n");
	else
		ft_printf("exit\n");
	if (split_size(splitline) == 1 || split_size(splitline) == 2)
		exit_normal(minidata, splitline, &exitno);
	err = error_exit(2, 0);
	update_return(minidata, err);
	rl_on_new_line();
}
