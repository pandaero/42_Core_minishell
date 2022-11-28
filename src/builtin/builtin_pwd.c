/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:58 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/27 00:57:40 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function prints the current working directory where the shell is acting.
void	builtin_pwd(t_minidata *minidata)
{
	ft_printf("%s\n", find_env_var_list(minidata, "PWD")->value);
}
