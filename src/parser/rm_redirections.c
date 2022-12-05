/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:18:06 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/05 21:52:07 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function that saves redirection and file name
static int	add_new_redirection(t_word *tmp, t_parser_tools *parser_tools)
{
	t_word	*node;
	int		index_1;
	int		index_2;

	node = newlex(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
		parser_error(1, parser_tools->minidata, parser_tools->lexer_list);
	add_back_lex(&parser_tools->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	lexerdelone(&parser_tools->lexer_list, index_1);
	lexerdelone(&parser_tools->lexer_list, index_2);
	parser_tools->num_reds++;
	return (0);
}

//Function checks for redirections.
void	rm_redirections(t_parser_tools *parser_tools)
{
	t_word	*tmp;

	tmp = parser_tools->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(2, parser_tools->minidata, parser_tools->lexer_list);
	if (tmp->next->token)
		parser_token_error(parser_tools->minidata,
			parser_tools->lexer_list, tmp->next->token);
	if ((tmp->token >= GREAT && tmp->token <= LESS_LESS))
		add_new_redirection(tmp, parser_tools);
	rm_redirections(parser_tools);
}
