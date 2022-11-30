/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/30 08:38:51 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include "stdio.h"

int ft_init_minidata(t_minidata *minidata)
{
    minidata->simple_cmds = NULL;
    minidata->lexer_l = NULL;
    minidata->reset = false;
    return (1);
}

int reset_tools(t_minidata *minidata)
{
    simple_cmdsclear(&minidata->simple_cmds);
    free(minidata->currline);
    if (minidata->pid)
        free(minidata->pid);
    minidata->reset = true;
    ft_init_minidata(minidata);
    main_loop(minidata);
    return (1);
}