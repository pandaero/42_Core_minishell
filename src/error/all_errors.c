/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:57:59 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/23 11:48:19 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	allerrors(int error, t_minidata *minidata)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n",
			STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
	(void) minidata;
	return (EXIT_FAILURE);
}

//Function handles an "command not found" error.
int	error_cmd_nf(char *line)
{
	write(STDERR_FILENO, "minishell: command not found: ", 30);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, "\n", 1);
	return (127);
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
