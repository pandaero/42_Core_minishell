/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:44 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/24 15:19:04 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

// Function to create a new element of the list and init data of elem
t_word *newlex(char *s, int token)
{
	t_word *new_elem;
	static int i = 0;

	new_elem = (t_word *)malloc(sizeof(t_word));
	if (new_elem == 0)
		return (0);
	new_elem->str = s;
	// ft_printf("TOKEN = %d\n" , token);
	new_elem->token = token;
	new_elem->i = i++;
	// ft_printf("i = %d\n" , i);
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

// Function to add element back of the list
void	add_back_lex(t_word **lst, t_word *new)
{
	t_word *tmp;

	tmp = *lst;
	if (*lst == NULL)// to add first element
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next; // new element
	tmp->next = new;// pointer to next
	new->prev = tmp;// pointer to previous
}
// Function to put all tokens in separate container(doubly linked list)
int add_unitto_lexer(char *s,  t_tokens token, t_word **lexer_l)
{
	t_word *word;

	// ft_printf("%s\n", s);
	word = newlex(s, token);
	if (word == 0)
		return (0);
	add_back_lex(lexer_l,word);
	return (1);
}
