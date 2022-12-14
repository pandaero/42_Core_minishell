/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:40:14 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/14 18:12:29 by zyunusov         ###   ########.fr       */
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
	t_word	*tmp;

	i = 0;
	if (rm_redirections(parser_tools))
		return (NULL);
	arg_size = count_args(parser_tools->lexer_list);
	str = malloc(sizeof(char *) * (arg_size + 1));
	if (!str)
	{
		parser_error(1, parser_tools->minidata, parser_tools->lexer_list);
		return (NULL);
	}
	tmp = parser_tools->lexer_list;
	while (i < arg_size)
	{
		if (tmp->str)
		{
			str[i] = ft_strdup(tmp->str);
			lexerdelone(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		i++;
	}
	str[i] = NULL;
	return (simple_cmdnew(str, arg_size, \
			parser_tools->num_reds, parser_tools->redirections));
}

// Function to check pipe errors
static int	handle_pipe_errors(t_minidata *minidata, t_token token)
{
	if (token == PIPE)
	{
		return (parser_token_error(minidata, minidata->lexer_list,
			minidata->lexer_list->token));
	}
	if (!minidata->lexer_list)
		return (parser_error(2, minidata, minidata->lexer_list));
	return (EXIT_SUCCESS);
}

int	start_parser(t_minidata *minidata)
{
	t_parser_tools	parser_tools;
	t_simple_cmds	*node;

	minidata->simple_cmds = NULL;
	count_pipes(minidata->lexer_list, minidata);
	if (minidata->lexer_list->token == PIPE)
		return (parser_token_error(minidata, minidata->lexer_list,
				minidata->lexer_list->token));
	while (minidata->lexer_list)
	{
		if (minidata->lexer_list && minidata->lexer_list->token == PIPE)
			lexerdelone(&minidata->lexer_list, minidata->lexer_list->i);
		if (minidata->lexer_list)
			if (handle_pipe_errors(minidata, minidata->lexer_list->token))
				return (EXIT_FAILURE);
		parser_tools = init_parser_tools(minidata->lexer_list, minidata);
		node = init_cmd(&parser_tools);
		if (!node)
			return (EXIT_FAILURE);
		if (!minidata->simple_cmds)
			minidata->simple_cmds = node;
		else
			simple_cmdsadd_back(&minidata->simple_cmds, node);
		minidata->lexer_list = parser_tools.lexer_list;
	}
	return (EXIT_SUCCESS);
}
