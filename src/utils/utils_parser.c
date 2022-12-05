/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:50:50 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 21:54:52 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function counts the number of pipe tokens present in the lexer linked list.
void	count_pipes(t_word *lexer_l, t_minidata *minidata)
{
	t_word	*tmp;

	tmp = lexer_l;
	minidata->num_pipes = 0;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			minidata->num_pipes++;
		tmp = tmp->next;
	}
}

//Function to intialize parser_tools
t_parser_tools	init_parser_tools(t_word *lexer_l, t_minidata *minidata)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = lexer_l;
	parser_tools.redirections = NULL;
	parser_tools.num_reds = 0;
	parser_tools.minidata = minidata;
	return (parser_tools);
}

//Function to count the number of arguments within a pipe. 
int	count_args(t_word *lexer_l)
{
	t_word	*tmp;
	int		i;

	i = 0;
	tmp = lexer_l;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

