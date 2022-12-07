/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:20:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/07 11:55:20 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

//Function prints out the "no arguments accepted" error on standard error.
void	error_args(int argc, char **argv)
{
	int	i;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	i = 1;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDERR_FILENO);
		if (i != argc - 1)
			ft_putstr_fd(" ", STDERR_FILENO);
		else
			ft_putstr_fd(": ", STDERR_FILENO);
		i++;
	}
	ft_putstr_fd("No arguments accepted\n", STDERR_FILENO);
}