/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:20:32 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/20 18:48:26 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_handle_quotes(int i, char *s, char del)
{
    int j;
    
    j = 0;
    if (s[i + j] == del) // if char == to qoute
    {
        j++; // skip
        while(s[i + j] != del && s[i + j] != '\0') // and read until quote
            j++;
        j++; // skip quote
    }
    return (j); // return word and quote counter
}