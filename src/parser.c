/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:27:25 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/20 01:36:17 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//Function finds the command element within a simple command line.
char	*findcommand(const char *line)
{
	char	**split;
	char	*cmd;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i] != 0)
		i++;
	while (i > 0)
	{
		free(split[i]);
		i--;
	}
	cmd = split[0];
	free(split);
	return (cmd);
}
