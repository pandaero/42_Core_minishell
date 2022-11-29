/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/29 22:17:25 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int reset_tools(t_minidata *minidata)
{
    simple_cmdsclear(&minidata->simple_cmds);
    free(minidata->currline);
    if (minidata->pid)
        free(minidata->pid);
    setup_signal();
    minidata->reset = true;
    main_loop(minidata);
    return (1);
}