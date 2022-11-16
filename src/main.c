/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:53:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/16 18:15:33 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

//Program is an interactive shell.
int	main(int argc, char **argv, char **env)
{
	char	*line;

	line = (char *) 1;
	if (argv && env && argc == 1)
	{
		while (line != 0)
		{
			setup_signal();
			line = readline("$>");
			if (validline(line) == 1)
			{
				add_history (line);
				ft_printf("Command line was valid.\n");
			}
			else if (validline(line) == -1)
				error_cmd_nf(line);
			free(line);
		}
	}
	else
		write(STDERR, "No arguments are required", 25);
	return (0);
}
