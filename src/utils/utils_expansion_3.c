/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:25:23 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/30 00:27:13 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function determines whether a string contains single quotes.
int	contains_squotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

//Function determines the number of single quotes in a string.
int	count_squotes(const char *str)
{
	int	i;
	int	ct;

	ct = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			ct++;
		i++;
	}
	return (ct);
}

//Function cleans single quotes from a string. Frees input string.
char	*clean_squotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	if (contains_squotes(str) == 0)
		return (str);
	new = (char *)malloc((ft_strlen(str) - count_squotes(str) + 1) \
			* sizeof(char));
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == '\'')
			i++;
		if (!str[i])
			break ;	
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}
