/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:05 by zyunusov          #+#    #+#             */
/*   Updated: 2023/01/02 13:09:58 by zyunusov         ###   ########.fr       */
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
		if (token_arr[i][0] == ch)
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
		if (!add_lexer_node(NULL, GREAT_GREAT, lexer_l))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_token(s[i + 1]) == LESS)
	{
		if (!add_lexer_node(NULL, LESS_LESS, lexer_l))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_lexer_node(NULL, token, lexer_l))
			return (-1);
		return (1);
	}
	return (0);
}
