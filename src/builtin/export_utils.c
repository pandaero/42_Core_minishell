/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:20:16 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/29 13:21:33 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

char	*check_value(char **splitassign, t_minidata *minidata)
{
	char	*value;

	if (splitassign[1] != NULL)
		value = string_expansion(minidata, splitassign[1]);
	else
		value = ft_strdup(" ");
	return (value);
}
