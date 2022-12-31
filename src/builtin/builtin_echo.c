/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:18:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/15 20:36:02 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

// // Function prints out the invalid input error to standard error.
void	error_inv_input(t_minidata *minidata)
{
	ft_putstr_fd("minishell: invalid input\n", STDERR_FILENO);
	update_return(minidata, 2);
}

static void	ft_print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

void	builtin_echo(t_minidata *minidata)
{
	int	i;
	int	j;
	int	n_op;

	i = 1;
	n_op = 0;
	while (minidata->simple_cmds->str[i] \
		&& minidata->simple_cmds->str[i][0] == '-' \
		&& minidata->simple_cmds->str[i][1] == 'n')
	{
		j = 1;
		while (minidata->simple_cmds->str[i][j] == 'n')
			j++;
		if (minidata->simple_cmds->str[i][j] == '\0')
			n_op = 1;
		else
			break ;
		i++;
	}
	ft_print_lines(i, minidata->simple_cmds->str, STDOUT_FILENO);
	if (n_op == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	update_return(minidata, EXIT_SUCCESS);
}
