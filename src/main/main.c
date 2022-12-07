/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/07 11:53:41 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

//Function exits the program cleanly.
static void	cleanexit(t_minidata *minidata)
{
	free_minidata(minidata);
	exit(EXIT_SUCCESS);
}

//Function performs the terminal attributes setting and readline initialisation.
int	main_loop(t_minidata *minidata)
{
	struct termios	termparams;
	struct termios	newtermparams;
	int				ret;

	ret = tcgetattr(0, &termparams);
	newtermparams = termparams;
	newtermparams.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(0, 0, &newtermparams);
	(void) ret;
	minidata->currline = readline(PROMPT);
	if (minidata->currline == 0)
		cleanexit(minidata);
	if (minidata->currline[0] == '\0')
		return (reset_tools(minidata));
	add_history (minidata->currline);
	parser(minidata);
	prepare_executor(minidata);
	reset_tools(minidata);
	return (1);
}

//Program is an interactive shell.
int	main(int argc, char **argv, char **env)
{
	t_minidata	*minidata;

	if (argv && argc == 1)
	{
		minidata = init_minidata(env);
		ft_init_minidata(minidata);
		setup_signal();
		main_loop(minidata);
	}
	else
		error_args(argc, argv);
	return (0);
}
