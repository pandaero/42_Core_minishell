/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:59:09 by zyunusov          #+#    #+#             */
/*   Updated: 2023/01/06 16:11:52 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function navigates to a closing delimiter (from a starting location).
int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del && str[i + 1] != '\0')
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}

//Function determines the command units in non-token command line. Adds to list.
static int	read_simple(int i, char *str, t_word **lexer_l)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes(i + j, str, 34);
		j += handle_quotes(i + j, str, 39);
		if (str[i + j] == '\0')
			break ;
		if (is_space(str[i + j]))
			break ;
		else
			j++;
	}
	if (add_lexer_node(ft_substr(str, i, j), 0, lexer_l) == 0)
		return (-1);
	return (j);
}

//Function fills the lexer linked list with command units from the command line.
int	read_token(t_minidata *minidata)
{
	int	i;
	int	j;

	i = 0;
	while (minidata->currline[i])
	{
		j = 0;
		i += skip_spaces(minidata->currline, i);
		if (check_token(minidata->currline[i]))
			j = handle_token(i, minidata->currline, &minidata->lexer_list);
		else
			j = read_simple(i, minidata->currline, &minidata->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
