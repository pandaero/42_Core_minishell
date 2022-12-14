/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:58:00 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/20 15:58:00 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function handles single quote expansions.
static char	*squote_string_expansion(t_minidata *minidata, char *str)
{
	char	*new;

	new = NULL;
	if (count_squotes(str) % 2 == 0)
		new = clean_squotes(str);
	else
		error_inv_input(minidata);
	if (str != NULL)
		free(str);
	return (new);
}

//Function handles double quote expansions.
static char	*dquote_string_expansion(t_minidata *minidata, char *str)
{
	char	*new;

	new = NULL;
	if (count_dquotes(str) % 2 == 0)
	{
		new = var_expansion(minidata, str);
		new = clean_dquotes(new);
	}
	else
		error_inv_input(minidata);
	free(str);
	return (new);
}

//Function removes the corresponding quotes from a string.
static char	*dollar_clean_quotes(char qt, char *new, char *str, char *temp)
{
	if (qt == 's')
		temp = clean_squotes(str);
	else
		temp = clean_dquotes(str);
	new = ft_substr(temp, 1, ft_strlen(temp));
	free(temp);
	return (new);
}

//Function handles dollar sign expansions.
static char	*dollar_string_expansion(t_minidata *minidata, char *str)
{
	char	*new;
	char	*temp;

	new = NULL;
	temp = NULL;
	if (str[1] == '\'')
	{
		if (count_squotes(str) % 2 == 0)
			new = dollar_clean_quotes('s', new, str, temp);
		else
			error_inv_input(minidata);
	}
	else if (str[1] == '\"')
	{
		if (count_dquotes(str) % 2 == 0)
			new = dollar_clean_quotes('d', new, str, temp);
		else
			error_inv_input(minidata);
	}
	else
		new = var_expansion(minidata, str);
	return (new);
}

//Function interprets quotes in a string to give "cleaned" output.
char	*string_expansion(t_minidata *minidata, char *str)
{
	char	*new;

	new = NULL;
	if (str[0] == '\"')
		return (dquote_string_expansion(minidata, str));
	else if (str[0] == '\'')
		return (squote_string_expansion(minidata, str));
	else if (str[0] == '$')
	{
		new = dollar_string_expansion(minidata, str);
		free(str);
		return (new);
	}
	else
		new = var_expansion(minidata, str);
	if (str != NULL)
		free(str);
	return (new);
}
