/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/20 03:12:49 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

//Function performs the terminal attributes setting and readline initialisation.
static void	main_loop(t_minidata *minidata)
{
	char			*line;
	struct termios	termparams;
	struct termios	newtermparams;
	int				ret;

	ret = tcgetattr(0, &termparams);
	newtermparams = termparams;
	newtermparams.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(0, 0, &newtermparams);
	(void) ret;
	line = (char *) 1;
	while (line != 0)
	{
		setup_signal();
		line = readline(PROMPT);
		if (validline(line, minidata) == 1)
		{
			add_history (line);
			ft_printf("Command line was valid.\n");
		}
		else
			error_cmd_nf(line);
		free(line);
	}
}

//Program is an interactive shell.
int	main(int argc, char **argv, char **env)
{
	t_minidata	*minidata;

	if (argv && argc == 1)
	{
		minidata = (t_minidata *)malloc(sizeof(t_minidata));
		minidata->env = env;
		init_minidata(minidata);
		main_loop(minidata);
	}
	else
		write(STDERR, "No arguments are required", 25);
	return (0);
}
