/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:53:42 by pandalaf          #+#    #+#             */
/*   Updated: 2023/01/02 13:12:15 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function checks whether a character is a spacing character.
int	is_space(char ch)
{
	return (ch == ' ' || (ch > 8 && ch < 14));
}

//Function skips spacing characters (within a char string).
int	skip_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (is_space(line[i + j]))
		j++;
	return (j);
}
