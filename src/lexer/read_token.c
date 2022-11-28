/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:59:09 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/28 03:15:22 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check for word separator
static int	ft_is_space(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

// function to skip separators
static int	ft_spaces_skip(char *line, int i)
{
	int	j;

	j = 0;
	while (ft_is_space(line[i + j]))
		j++;
	return (j);
}

// function to read only words(cmds)
static int	ft_read_words(int i, char *s, t_word **lexer_l)
{
	int	j;

	j = 0;
	while (s[i + j] && (!check_token(s[i + j])))
	{
		j += ft_handle_quotes(i + j, s, 34);
		j += ft_handle_quotes(i + j, s, 39);
		if (ft_is_space(s[i + j]))
			break ;
		else
			j++;
	}
	if (add_unitto_lexer(ft_substr(s, i, j), 0, lexer_l) == 0)
		return (-1);
	return (j);
}

// function to read from string, to divide to tokens
int	ft_read_token(t_minidata *minidata)
{
	int	i;
	int	j;

	i = 0;
	while (minidata->currline[i])
	{
		j = 0;
		i += ft_spaces_skip(minidata->currline, i);
		if (check_token(minidata->currline[i]))
			j = handle_token(i, minidata->currline, &minidata->lexer_l);
		else
			j = ft_read_words(i, minidata->currline, &minidata->lexer_l);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
