/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:44:26 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/30 10:36:52 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// Function to intialize parser_tools
t_parser_tools	init_parser_tools(t_word *lexer_l, t_minidata *minidata)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_l = lexer_l;
	parser_tools.redirections = NULL;
	parser_tools.num_red = 0;
	parser_tools.minidata = minidata;
	return (parser_tools);
}

// Function to count pipes in currline
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

// Function to count arguments until pipe 
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
