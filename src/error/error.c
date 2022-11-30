/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:20:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/30 13:44:09 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function handles an "command not found" error.
void	error_cmd_nf(char *line)
{
	char	*cnf;

	write(STDERR_FILENO, "minishell: command not found: ", 30);
	cnf = findcommand(line);
	write(STDERR_FILENO, cnf, ft_strlen(cnf));
	write(STDERR_FILENO, "\n", 1);
	free(cnf);
}

//Function handles an "no permission cmd" error.
void	error_cmd_np(const char *line)
{
	char	*cnf;

	write(STDERR_FILENO, "minishell: permission denied: ", 30);
	cnf = findcommand(line);
	write(STDERR_FILENO, cnf, ft_strlen(cnf));
	write(STDERR_FILENO, "\n", 1);
	free(cnf);
}

//Function handles an error in signal action setup.
void	error_sig(void)
{
	write(STDERR_FILENO, "error: couldn't set-up signal handling", 38);
	exit(EXIT_FAILURE);
}

//Function prints out a syntax error message.
void	error_syntax(int type)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token ", 46);
	if (type == 1)
		write(STDERR_FILENO, "`|'", 3);
	else
		write(STDERR_FILENO, "`newline'", 9);
	ft_putchar_fd('\n', STDERR_FILENO);
}
