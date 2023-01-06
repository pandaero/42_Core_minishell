/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:27:25 by pandalaf          #+#    #+#             */
/*   Updated: 2023/01/02 13:35:00 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
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

//Function performs the parsing of a command line.
int	parser(t_minidata *minidata)
{
	if (!is_valid_quotes(minidata->currline))
		return (allerrors(0, minidata));
	if (!read_token(minidata))
		return (allerrors(1, minidata));
	if (start_parser(minidata))
	{
		update_return(minidata, 258);
		loop_reset(minidata);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
