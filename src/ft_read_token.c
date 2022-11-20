/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:59:09 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/20 18:55:27 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_is_space(char c) // check for word separator
{
    return (c == ' ' || (c > 8 && c < 14));
}

static int ft_spaces_skip(char *line, int i)// function to skip separators
{
    int j;

    j = 0;
    while (ft_is_space(line[i + j]))
        j++;
    return (j);
}

static int ft_read_words(int i, char *s)//, t_lexer **lexer_l)// function to read only words(cmds)
{
    int j;

    j = 0;
    while (s[i + j])
    {
        j += ft_handle_quotes(i + j, s, 34);
        j += ft_handle_quotes(i + j, s, 39);
        if (ft_is_space(s[i + j])) // will break when word already read
            break ;
        else
            j++;
    }
    // need to fill doubly linked list with words(tokens)
    return (j);
}

int ft_read_token(t_minidata *minidata)// function to read from string, to divide to tokens
{
    int i;
    int j;
    
    i = 0;
    while (minidata->args[i])
    {
        j = 0;
        i += ft_spaces_skip(minidata->args, i); //to skip spaces before cmd
        if (minidata->args[i] == '>' || minidata->args[i] == '|')
            j += 1;
        // if(check_token(minidata->args[i])) // need to write function for pipes and redirections
            // j = ft_handle_token(i, minidata->args, &minidata->lexer_l); // function to hable pipes and redirections
        else
            j = ft_read_words(i, minidata->args); //, &minidata->lexer_l); // function to read words
        if (j < 0)
            return (0);
        i += j; // skips read word
        ft_printf("WORDS CHARS: %d\n", j);
    }
    return (1);
}
