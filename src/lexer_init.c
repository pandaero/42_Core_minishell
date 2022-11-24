/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 02:01:44 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/21 07:28:20 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

// Function to create a new element of the list and init data of elem
t_lexer *newlex(char *s, int token)
{
    t_lexer *new_elem;
    static int i = 0;

    new_elem = (t_lexer *)malloc(sizeof(t_lexer));
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
void    add_back_lex(t_lexer **lst, t_lexer *new)
{
    t_lexer *tmp;

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
int add_unitto_lexer(char *s,  t_tokens token, t_lexer **lexer_l)
{
    t_lexer *lexer_unit;

    // ft_printf("%s\n", s);
    lexer_unit = newlex(s, token);
    if (lexer_unit == 0)
        return (0);
    add_back_lex(lexer_l, lexer_unit);
    return (1);
}
