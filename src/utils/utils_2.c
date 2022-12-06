/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:14:40 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 18:47:07 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function reinserts a delimiter to a split-created 2D char array.
char	*unsplit(char **strarr, char delim)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*str;

	len = 0;
	i = 0;
	while (strarr[i])
	{
		len += ft_strlen(strarr[i]);
		i++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	k = 0;
	i = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j] != '\0')
		{
			str[k] = strarr[i][j];
			j++;
			k++;
		}
		if (strarr[i + 1] == NULL)
			break ;
		str[k] = delim;
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}

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
