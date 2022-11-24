/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:53:06 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/24 12:36:00 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function checks where a matching double or single quote is located.
static int find_matching_quotes (char *line, int i, int *num_del, int del)
{
	int j;

	j = i + 1;
	*num_del += 1;
	while (line[j] != '\0' && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

//Function checks whether there are valid quote expressions in the line.
int is_valid_quotes(char *line)
{
	int i;
	int s;
	int d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '\"')
			i += find_matching_quotes(line, i, &d, '\"');
		if (line[i] == '\'')
			i += find_matching_quotes(line, i, &s, '\'');
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}
