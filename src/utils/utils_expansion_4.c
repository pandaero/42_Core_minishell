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
	{
		new = var_expansion(minidata, str);
		new = clean_squotes(new);
	}
	else
		error_inv_input(minidata);
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
		{
			temp = clean_squotes(str);
			new = ft_substr(temp, 1, ft_strlen(temp));
			free(temp);
		}
		else
			error_inv_input(minidata);
	}
	else if (str[1] == '\"')
	{
		if (count_dquotes(str) % 2 == 0)
		{
			temp = clean_dquotes(str);
			new = ft_substr(temp, 1, ft_strlen(temp));
			free(temp);
		}
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
		return (dollar_string_expansion(minidata, str));
	else
		new = var_expansion(minidata, str);
	return (new);
}
