/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:40:14 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/07 11:31:02 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static t_simple_cmds	*init_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	int		dec;
	t_word	*tmp;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexer_l);
	dec = arg_size;
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->minidata, parser_tools->lexer_l);
	tmp = parser_tools->lexer_l;
	while (dec > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			//ft_printf("%d =%s\n",i, tmp->str);
			lexerdelone(&parser_tools->lexer_l, tmp->i);
			tmp = parser_tools->lexer_l;
		}
		dec--;
	}
	return (simple_cmdnew(str, arg_size, \
			parser_tools->num_red, parser_tools->redirections));
}

// Function to check pipe errors
static int	handle_pipe_errors(t_minidata *minidata, t_tokens token)
{
	if (token == PIPE)
	{
		parser_token_error(minidata, minidata->lexer_l,
			minidata->lexer_l->token);
		return (EXIT_FAILURE);
	}
	if (!minidata->lexer_l)
	{
		parser_error(2, minidata, minidata->lexer_l);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	start_parser(t_minidata *minidata)
{
	t_parser_tools	parser_tools;
	t_simple_cmds	*node;

	minidata->simple_cmds = NULL;
	count_pipes(minidata->lexer_l, minidata);
	if (minidata->lexer_l->token == PIPE)
		return (parser_token_error(minidata, minidata->lexer_l,
				minidata->lexer_l->token));
	while (minidata->lexer_l)
	{
		if (minidata->lexer_l && minidata->lexer_l->token == PIPE)
			lexerdelone(&minidata->lexer_l, minidata->lexer_l->i);
		if (handle_pipe_errors(minidata, minidata->lexer_l->token))
			return (EXIT_FAILURE);
		parser_tools = init_parser_tools(minidata->lexer_l, minidata);
		node = init_cmd(&parser_tools);
		if (!node)
			parser_error(2, minidata, parser_tools.lexer_l);
		if (!minidata->simple_cmds)
			minidata->simple_cmds = node;
		else
			simple_cmdsadd_back(&minidata->simple_cmds, node);
		minidata->lexer_l = parser_tools.lexer_l;
	}
	return (EXIT_SUCCESS);
}
