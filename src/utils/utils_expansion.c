/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:05:49 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/23 13:17:554 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function expands variables if present in an expression.
char	*var_expansion(t_minidata *minidata, const char *expression)
{
	int		i;
	char	*expansion;
	char	*temp;

	expansion = ft_strdup(expression);
	i = 0;
	while (contains_variables(expansion) == 1)
	{
		i = 0;
		while (expansion[i] != '\0')
		{
			if (expansion[i] == '$')
			{
				temp = ft_strdup(expansion);
				free(expansion);
				expansion = expand_var(minidata, temp, i);
				free(temp);
				break ;
			}
			i++;
		}
	}
	return (expansion);
}

static char	*expand_extra(t_minidata *minidata, char *str, char *pre, char ch)
{
	char	*new;
	char	*exp;
	char	*post;
	char	*value;
	int		ii[2];

	ii[0] = 0;
	while (str[ii[0]] != '$')
		ii[0]++;
	ii[1] = 0;
	while (str[ii[1]] != '\0')
		ii[1]++;
	post = ft_substr(str, ii[0] + 2, ii[1] - ii[0]);
	if (ch == '$')
		value = minidata->dollar;
	if (ch == '?')
		value = minidata->last_return;
	new = ft_strjoin(pre, value);
	exp = ft_strjoin(new, post);
	free(pre);
	free(post);
	free(new);
	return (exp);
}

//Function frees the pointers used in the expand_var function.
static void	free_expand_var(char *post, char *pre, char *var, char *new)
{
	free(pre);
	free(var);
	free(new);
	free(post);
}

//Function
char	*expand_var_2(t_minidata *minidata, t_expand expand, char *str, t_ii ii)
{
	if (str[ii.j] == '\0')
		expand.post = ft_strdup("");
	else
		expand.post = ft_substr(str, ii.j, ft_strlen(str));
	if (ii.k == 0)
		expand.var = ft_substr(str, ii.i + 1, ii.j - ii.i - 1);
	else
		expand.var = ft_strdup("");
	expand.nnew = ft_strjoin(expand.pre, \
					find_env_var_list(minidata, expand.var)->value);
	expand.newnew = ft_strjoin(expand.nnew, expand.post);
	free_expand_var(expand.post, expand.pre, expand.var, expand.nnew);
	return (expand.newnew);
}

//Function expands a variable within an expression, given a starting point.
char	*expand_var(t_minidata *minidata, char *str, int i)
{
	t_expand	expand;
	t_ii		ii;

	ii.k = 0;
	if (i == 0)
		expand.pre = ft_strdup("");
	else
		expand.pre = ft_substr(str, 0, i);
	ii.j = i + 1;
	if (str[ii.j] == '$' || str[ii.j] == '?')
		return (expand_extra(minidata, str, expand.pre, str[ii.j]));
	if (str[ii.j] >= '0' && str[ii.j] <= '9')
	{
		ii.j++;
		ii.k++;
	}
	else
	{
		while (str[ii.j] != '\0' && is_var(str[ii.j]) == 1)
		ii.j++;
	}
	ii.i = i;
	return (expand_var_2(minidata, expand, str, ii));
}
