/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:09:09 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/29 23:53:04 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

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

//Function determines whether a string contains double quotes.
int	contains_dquotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

//Function determines the number of double quotes in a string.
int	count_dquotes(const char *str)
{
	int	i;
	int	ct;

	ct = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			ct++;
		i++;
	}
	return (ct);
}

//Function cleans double quotes from a string. Frees input string.
char	*clean_dquotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	if (contains_dquotes(str) == 0)
		return (str);
	new = (char *)malloc((ft_strlen(str) - count_dquotes(str) + 1) \
			* sizeof(char));
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == '\"')
			i++;
		new[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new);
}
