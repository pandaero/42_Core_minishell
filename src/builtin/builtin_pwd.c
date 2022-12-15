/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:19:58 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/14 17:01:23 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function prints the current working directory where the shell is acting.
void	builtin_pwd(t_minidata *minidata)
{
	ft_printf("%s\n", find_env_var_list(minidata, "PWD")->value);
	update_return(minidata, EXIT_SUCCESS);
}
