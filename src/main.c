/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 16:46:44 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

static void	main_loop(t_minidata *minidata)
{
	char	*line;

	line = (char *) 1;
	while (line != 0)
	{
		setup_signal();
		line = readline("$>");
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
