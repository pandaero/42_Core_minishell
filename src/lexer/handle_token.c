/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:05 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/05 19:22:34 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Function determines the type of special token that a character is.
t_token	check_token(char ch)
{
	int			i;
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == (int) ch)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

//Function adds command line units to the lexer linked list accordingly.
int	handle_token(int i, char *s, t_word **lexer_l)
{
	t_token	token;

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
