/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/20 18:48:40 by zyunusov         ###   ########.fr       */
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
	struct termios	termparams;
	struct termios	newtermparams;
	int				ret;

	ret = tcgetattr(0, &termparams);
	newtermparams = termparams;
	newtermparams.c_lflag &= ~ECHOCTL;
	ret = tcsetattr(0, 0, &newtermparams);
	(void) ret;
	minidata->args = (char *) 1;
	while (minidata->args != 0)
	{
		setup_signal();
		minidata->args = readline(PROMPT);
		if (ft_count_quotes(minidata->args) == 0)
		{
			add_history (minidata->args);
			ft_printf("syntax error: unable to locate closing quotation\n");
			return ;
		}
		if (ft_read_token(minidata) == 0)
		{
			ft_printf("\n");
		}
		if (validline(minidata) == 1)
		{
			add_history (minidata->args);
			ft_printf("Command line was valid.\n");
		}
		else
			error_cmd_nf(minidata->args);
		free(minidata->args);
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
