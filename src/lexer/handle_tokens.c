/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:05 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/24 15:02:30 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens check_token(int c)
{
	static int token_arr[3][2] = {
	{'|', PIPE},
	{'>', GREAT},
	{'<', LESS},
	};
	int i;
	
	i = 0;
	while(i < 3)
	{
		if (token_arr[i][0] == c)// if passed token equals to 1 elem from 2d arr
			return (token_arr[i][1]); // return token that is found
		i++;
	}
	return (0);
}

int handle_token(int i, char *s, t_word **lexer_l)
{
	t_tokens token;

	token = check_token(s[i]);
	if (token == GREAT && check_token(s[i + 1]) == GREAT)
	{
		if (add_unitto_lexer(NULL, GREAT_GREAT, lexer_l) == 0)
			return (-1);
		return (2); // 2 to skip <<
	}
	else if (token == LESS && check_token(s[i + 1]) == LESS)
	{
		if (add_unitto_lexer(NULL, LESS_LESS, lexer_l) == 0)
			return (-1);
		return (2); // 2 to skip <<
	}
	else if (token)
	{
		if (add_unitto_lexer(NULL, token, lexer_l) == 0)
			return (-1);
		return (1); // to skip | < >
	}
	return (0);
}
