/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplit_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:29:19 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/04 19:32:57 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

static char	*join_split_str(char **split_str, char *new_str)
{
	char	*temp;
	char	*add_space;
	int		i;

	temp = ft_strdup(split_str[0]);
	i = 1;
	while (split_str[i])
	{
		new_str = temp;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		temp = ft_strjoin(add_space, split_str[i]);
		free(add_space);
		i++;
	}
	new_str = temp;
	return (new_str);
}

char	**resplit_str(char **double_arr)
{
	char	**result;
	char	*joined_str;

	joined_str = join_split_str(double_arr, NULL);
	free_split(double_arr);
	result = ft_split(joined_str, ' ');
	free(joined_str);
	joined_str = join_split_str(result, NULL);
	free_split(result);
	result = ft_split(joined_str, ' ');
	free(joined_str);
	return (result);
}