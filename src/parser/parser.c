/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:27:25 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/16 14:20:11 by zyunusov         ###   ########.fr       */
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

//Function acts when the input command line is a valid one.
// static void	execution(t_minidata *minidata)
// {
// 	if (is_builtincmd(minidata) > 0)
// 		builtin_execution(minidata);
// 	//path (check permissions)
// 	//direct (check permissions)
// }

//Function performs the parsing of a command line.
int	parser(t_minidata *minidata)
{
	if (is_valid_quotes(minidata->currline) == 0)
		return (allerrors(0, minidata));
	if (read_token(minidata) == 0)
		return (allerrors(1, minidata));
	if (start_parser(minidata))
	{
		update_return(minidata, 258);
		loop_reset_err(minidata);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
