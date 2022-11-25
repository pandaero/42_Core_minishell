/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:44:26 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/25 14:36:18 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_pipes(t_word *lexer_l, t_minidata *minidata)
{
	t_word	*tmp;

	tmp = lexer_l;
	minidata->num_pipes = 0;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			minidata->num_pipes++;
		tmp = tmp->next;
	}
}
