/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:52:27 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/09 20:47:22 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int prepare_executor(t_minidata *minidata)
{
    if (minidata->num_pipes == 0)
    {
        minidata->pid = ft_calloc(2, sizeof(int));
        // ft_printf("SINGLE\n");
        // single_cmd(minidata);
    }
    else
    {
        minidata->pid = ft_calloc(sizeof(int), minidata->num_pipes + 2); // need to think about it 
        if (!minidata->pid)
            return (allerrors(1, minidata));
        // ft_printf("DOUBLE\n");
        start_executor(minidata);
    }
    return (EXIT_SUCCESS);
}