/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:39:06 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 19:57:38 by pandalaf         ###   ########.fr       */
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
	write(STDERR, "minishell: exit: ", 17);
	if (err == 1)
	{
		write(STDERR, arg, ft_strlen(arg));
		write(STDERR, ": numeric argument required", 27);
	}
	else
		write(STDERR, "too many arguments", 18);
	write(STDERR, "\n", 1);
	return (255);
}

//Function frees elements and exits the program with given number.
static void	free_exit(int ret, char **splitline, t_minidata *minidata)
{
	free_split(splitline);
	free_split(minidata->builtincmds);
	free(minidata->currline);
	free(minidata);
	exit(ret);
}

//Function exits the program cleanly.
void	builtin_exit(t_minidata *minidata)
{
	char	**splitline;
	int		exitno;

	exitno = 0;
	splitline = ft_split(minidata->currline, ' ');
	if (split_size(splitline) == 1 || split_size(splitline) == 2)
	{
		if (split_size(splitline) == 2 && (ft_atol(splitline[1]) == -1 || \
			is_validnum(splitline[1]) == 0))
			exitno = error_exit(1, splitline[1]);
		else if (split_size(splitline) == 2)
		{
			if (ft_atol(splitline[1]) > 0)
				exitno = ft_atol(splitline[1]) % 256;
			else
				exitno = (ft_atol(splitline[1]) * -1) % 256;
		}
		else
			exitno = EXIT_SUCCESS;
		free_exit(exitno, splitline, minidata);
	}
	error_exit(2, 0);
	rl_on_new_line();
}
