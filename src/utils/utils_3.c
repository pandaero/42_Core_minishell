/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:53:42 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 22:58:38 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function checks whether a character is a spacing character.
int	is_space(char ch)
{
	if (ch == ' ' || (ch > 8 && ch < 14))
		return (1);
	return (0);
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
