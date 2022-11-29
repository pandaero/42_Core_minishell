/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:18:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/30 00:33:51 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function prints out the invalid input error to standard error.
void	error_inv_input(void)
{
	ft_putstr_fd("minishell: invalid input\n", STDERR_FILENO);
}

//Function writes a given string to the terminal. With/out newline.
void	builtin_echo(t_minidata *minidata)
{
	char	**splitline;
	char	*str;
	char	*out;
	int		i;

	splitline = ft_split(minidata->currline, ' ');
	i = 1;
	while (splitline[i])
	{
		if (ft_strncmp(splitline[i], "-n", 3) == 0)
		{
			i++;
			continue ;
		}
		if (splitline[i][0] == '\"')
		{
			if (count_dquotes(splitline[i]) % 2 == 0)
			{
				str = var_expansion(minidata, splitline[i]);
				str = clean_dquotes(str);
			}
			else
				error_inv_input();
		}
		else if (splitline[i][0] == '\'')
		{
			if (count_squotes(splitline[i]) % 2 == 0)
			{
				str = ft_strdup(splitline[i]);
				str = clean_squotes(str);
			}
			else
				error_inv_input();
		}
		else
			str = var_expansion(minidata, splitline[i]);
		i++;
	}
	free_split(splitline);
	if (ft_strncmp(splitline[1], "-n", 3) == 0)
		out = ft_strdup(str);
	else 
		out = ft_strjoin(str, "\n");
	free(str);
	ft_putstr_fd(out, 1);
	free(out);
}
