/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:09:09 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/27 01:09:28 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function checks whether the input character is valid for an environment var.
int	is_var(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	if (ch >= 'a' && ch <= 'z')
		return (1);
	if (ch >= '0' && ch <= '9')
		return (1);
	if (ch == '_')
		return (1);
	return (0);
}

//Function determines if there are variables present in an expression.
int	contains_variables(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
