/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:40:14 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/28 16:51:07 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	handle_pipe_errors(t_minidata *minidata, t_tokens token)
{
	if (token == PIPE)
	{
		parser_token_error(minidata, minidata->lexer_l, minidata->lexer_l->token);
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
	count_pipes(minidata->lexer_l, minidata);
	if (minidata->lexer_l->token == PIPE)
		return (parser_token_error(minidata, minidata->lexer_l, minidata->lexer_l->token));
	while (minidata->lexer_l)
	{
		if (minidata->lexer_l && minidata->lexer_l->token == PIPE)
			lexerdelone(&minidata->lexer_l, minidata->lexer_l->i);
		if (handle_pipe_errors(minidata, minidata->lexer_l->token))
			return (EXIT_FAILURE);
		break;
	}
	return (1);
}
