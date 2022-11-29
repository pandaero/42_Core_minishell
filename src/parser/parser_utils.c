/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:44:26 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/29 16:45:19 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parser_tools	init_parser_tools(t_word *lexer_l, t_minidata *minidata)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_l = lexer_l;
	parser_tools.redirections = NULL;
	parser_tools.num_red = 0;
	parser_tools.minidata = minidata;
	return (parser_tools);
}

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
