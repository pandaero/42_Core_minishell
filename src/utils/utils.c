/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:18:35 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/24 19:52:13 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <limits.h>

//Function returns the size of a ft_split-created array.
int	split_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//Function checks whether a character is a numeric one.
int	is_numeric(char ch)
{
	if (ft_isdigit(ch) == 1 || ch == '+' || ch == '-')
		return (1);
	return (0);
}

//Function checks whether a string contains a valid signed numeric declaration.
int	is_validnum(char *str)
{
	int	i;

	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
		if (str[i] == '\0')
			return (0);
		while (str[i] != '\0')
		{
			if (ft_isdigit(str[i]) == 0)
				return (0);
			i++;
		}
	}
	else
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (ft_isdigit(str[i]) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

//Function returns a long int with the value contained in the given char string.
long	ft_atol(char *str)
{
	int				sgn;
	unsigned long	sum;

	sum = 0;
	sgn = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sgn *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if ((sgn == 1 && sum > (unsigned long) LONG_MAX) || \
			(sgn == -1 && sum > (unsigned long) LONG_MAX + 1))
			return (-1);
	}
	return ((long) sgn * sum);
}

//Function returns a long long int with the value from the given char string.
long long	ft_atoll(char *str)
{
	int					sgn;
	unsigned long long	sum;

	sum = 0;
	sgn = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sgn *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if ((sgn == 1 && sum > (unsigned long long) LLONG_MAX) || \
			(sgn == -1 && sum > (unsigned long long) LLONG_MAX + 1))
			return (-1);
	}
	return ((long long) sgn * sum);
}
