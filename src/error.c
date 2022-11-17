/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:20:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/17 15:27:46 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function handles an "command not found" error.
void	error_cmd_nf(char *line, t_minidata *minidata)
{
	char	*cnf;

	write(STDERR, "minishell: command not found: ", 30);
	cnf = findcommand(line);
	write(STDERR, cnf, ft_strlen(cnf));
	write(STDERR, "\n", 1);
	free(cnf);
	free(line);
	free_minidata(minidata);
}

//Function handles an "no permission cmd" error.
void	error_cmd_np(const char *line)
{
	char	*cnf;

	write(STDERR, "minishell: permission denied: ", 30);
	cnf = findcommand(line);
	write(STDERR, cnf, ft_strlen(cnf));
	write(STDERR, "\n", 1);
	free(cnf);
}

//Function handles an error in signal action setup.
void	error_sig(void)
{
	write(STDERR, "error: couldn't set-up signal handling", 38);
	exit(EXIT_FAILURE);
}
