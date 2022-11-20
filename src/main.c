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
#include <readline/history.h>
#include <readline/readline.h>

// Better to create args variable in struct to line cuz it will be used a lot
static void	main_loop(t_minidata *minidata)
{
	minidata->args = (char *) 1;
	while (minidata->args != 0)
	{
		setup_signal();
		minidata->args = readline("$>");
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
