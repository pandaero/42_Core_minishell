/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/28 14:53:10 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int reset_tools(t_minidata *minidata)
{
    free(minidata->currline);
    setup_signal();
    minidata->reset = true;
    main_loop(minidata);
    return (1);
}