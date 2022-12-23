/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:18:13 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/15 20:36:02 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function prints out the invalid input error to standard error.
void	error_inv_input(t_minidata *minidata)
{
	ft_putstr_fd("minishell: invalid input\n", STDERR_FILENO);
	update_return(minidata, 2);
}

//Function peforms the double quote cleaning if necessary.
static void	echo_mini(t_minidata *minidata, t_echo *echo, int i)
{
	if (count_dquotes(echo->splitline[i]) % 2 == 0)
	{
		echo->str = var_expansion(minidata, echo->splitline[i]);
		echo->str = clean_dquotes(echo->str);
		update_return(minidata, EXIT_SUCCESS);
	}
	else
		error_inv_input(minidata);
}

//Function checks what type of expansion to perform and performs it.
static void	echo_inner(t_minidata *minidata, t_echo *echo, int i)
{
	if (echo->splitline[i][0] == '\"')
		echo_mini(minidata, echo, i);
	else if (echo->splitline[i][0] == '\'')
	{
		if (count_squotes(echo->splitline[i]) % 2 == 0)
		{
			echo->str = ft_strdup(echo->splitline[i]);
			echo->str = clean_squotes(echo->str);
			update_return(minidata, EXIT_SUCCESS);
		}
		else
			error_inv_input(minidata);
	}
	else
	{
		echo->str = var_expansion(minidata, echo->splitline[i]);
		update_return(minidata, EXIT_SUCCESS);
	}
}

//Function performs the interpretation for echo.
static void	echo_main(t_minidata *minidata, t_echo *echo, int i)
{
	char	*temp;

	while (echo->splitline[i])
	{
		if (ft_strncmp(echo->splitline[i], "-n", 3) == 0)
		{
			i++;
			continue ;
		}
		echo_inner(minidata, echo, i);
		if (echo->preout)
		{
			temp = ft_strjoin(" ", echo->str);
			echo->preout = ft_strjoin(echo->preout, temp);
			free(temp);
		}
		else
			echo->preout = ft_strdup(echo->str);
		free(echo->str);
		i++;
	}
}

//Function writes a given string to the terminal. With/out newline.
void	builtin_echo(t_minidata *minidata)
{
	t_echo	*func;
	int		i;

	func = (t_echo *)malloc(sizeof(t_echo));
	func->splitline = minidata->simple_cmds->str;
	func->preout = NULL;
	i = 1;
	if (split_size(func->splitline) == 1 || \
		(split_size(func->splitline) == 2 && \
		ft_strncmp(func->splitline[1], "-n", 3) == 0))
		func->preout = ft_strdup("");
	else
		echo_main(minidata, func, i);
	if (split_size(func->splitline) > 1 && \
		ft_strncmp(func->splitline[1], "-n", 3) == 0)
		func->finalout = ft_strdup(func->preout);
	else
		func->finalout = ft_strjoin(func->preout, "\n");
	free(func->preout);
	ft_putstr_fd(func->finalout, 1);
	free(func->finalout);
	free(func);
}
