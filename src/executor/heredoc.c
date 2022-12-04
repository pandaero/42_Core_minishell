/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:26:48 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/04 19:36:04 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"
// #include <unistd.h>
// #include <stdlib.h>

// char    *generate_heredoc_filename(void)
// {
//     static int  i = 0;
//     char        *num;
//     char        *file_name;

//     num = ft_itoa(i++);
//     file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
//     free(num);
//     return (file_name);
// }

// int send_heredoc(t_minidata *minidata, t_simple_cdms *cmd)
// {
//     t_word  *start;
//     int     sl;

//     start = cmd->redirections;
//     sl = EXIT_SUCCESS;
//     while (cmd->redirections)
//     {
//         if (cmd->redirections->token == LESS_LESS)
//         {
//             if (cmd->hd_file_name)
//                 free(cmd->hd_file_name);
//             cmd->hd_dile_name = 
//         }
//     }
// }