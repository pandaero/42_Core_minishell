/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 20:49:21 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

//Function acts when the input command line is a valid one.
static void	valid_line(t_minidata *minidata)
{
	//built-in
	if (is_builtincmd(minidata) > 0)
		builtin_execution(minidata);
	//path (check permissions)
	//direct (check permissions)
}

//Function performs the terminal attributes setting and readline initialisation.
static void	main_loop(t_minidata *minidata)
{
	struct termios	termparams;
	struct termios	newtermparams;
	int				ret;

	ret = tcgetattr(0, &termparams);
	newtermparams = termparams;
	newtermparams.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(0, 0, &newtermparams);
	(void) ret;
	minidata->currline = (char *) 1;
	while (minidata->currline != 0)
	{
		setup_signal();
		minidata->currline = readline(PROMPT);
		add_history (minidata->currline);
		if (minidata->currline[0] == '\0')
			continue ;
		if (is_valid_quotes(minidata->currline) == 0)
			ft_printf("syntax error: unable to locate closing quotation\n");
		if (ft_read_token(minidata) == 0)
			ft_printf("\n");
		if (is_validline(minidata) == 1)
			valid_line(minidata);
		else
			error_cmd_nf(minidata->currline);
		free(minidata->currline);
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
