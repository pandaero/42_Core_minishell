/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:05 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/28 03:16:43 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	handle_token(int i, char *s, t_word **lexer_l)
{
	t_tokens	token;

	token = check_token(s[i]);
	if (token == GREAT && check_token(s[i + 1]) == GREAT)
	{
		if (!add_unitto_lexer(NULL, GREAT_GREAT, lexer_l))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_token(s[i + 1]) == LESS)
	{
		if (!add_unitto_lexer(NULL, LESS_LESS, lexer_l))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_unitto_lexer(NULL, token, lexer_l))
			return (-1);
		return (1);
	}
	return (0);
}
