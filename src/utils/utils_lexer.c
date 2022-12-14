/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:19:08 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/14 17:44:40 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function creates a new element of the lexer list with the stated data.
t_word	*newlex(char *s, int token)
{
	t_word		*new_elem;
	static int	i;

	new_elem = (t_word *)malloc(sizeof(t_word));
	if (new_elem == 0)
		return (0);
	new_elem->str = s;
	new_elem->token = token;
	new_elem->i = i++;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

//Function adds a node to back of the lexer linked list.
void	add_back_lex(t_word **lst, t_word *new)
{
	t_word	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

//Function to add a new filled node to the lexer linked list.
int	add_lexer_node(char *s, t_token token, t_word **lexer_l)
{
	t_word	*word;

	word = newlex(s, token);
	if (word == 0)
		return (0);
	add_back_lex(lexer_l, word);
	return (1);
}
