/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:44 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/25 14:42:30 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

// Function to create a new element of the list and init data of elem
t_word	*newlex(char *s, int token)
{
	t_word		*new_elem;
	static int	i = 0;

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

// Function to add element back of the list
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

// Function to put all tokens in separate container(doubly linked list)
int	add_unitto_lexer(char *s, t_tokens token, t_word **lexer_l)
{
	t_word	*word;

	word = newlex(s, token);
	if (word == 0)
		return (0);
	add_back_lex(lexer_l, word);
	return (1);
}
