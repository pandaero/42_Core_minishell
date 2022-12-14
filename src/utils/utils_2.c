/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:14:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/15 20:36:09 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function returns the size of a 2D char array.
int	nonsplit_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//Function compares two strings and returns the difference at the first point.
int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;
	int	n;

	n = ft_strlen(str1);
	if (n < (int) ft_strlen(str2))
		n = ft_strlen(str2);
	i = 0;
	while (str1[i] == str2[i] && n > i + 1)
		i++;
	if (str1[i] != str2[i] && n != 0)
		return ((unsigned char) str1[i] - (unsigned char) str2[i]);
	return (0);
}

//Function updates the last return shell variable.
void	update_return(t_minidata *minidata, int ret)
{
	free(minidata->last_return);
	minidata->last_return = ft_itoa(ret);
}

//Function updates the dollar shell variable.
void	update_dollar(t_minidata *minidata, int doll)
{
	free(minidata->dollar);
	minidata->dollar = ft_itoa(doll);
}
