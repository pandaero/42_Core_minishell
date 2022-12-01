/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:08:30 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/30 13:30:26 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

//Function initialises the minidata.
t_minidata	*init_minidata(char **env)
{
	int			lvl;
	char		*alvl;
	char		*builtin;
	t_minidata	*new;

	new = (t_minidata *)malloc(sizeof(t_minidata));
	new->env = env;
	new->envlist = new_env_list();
	fill_env(new->envlist, env);
	lvl = ft_atoi(find_env_var_list(new, "SHLVL")->value) + 1;
	alvl = ft_itoa(lvl);
	set_env_var(new, "SHLVL", alvl);
	free(alvl);
	builtin = ft_strdup("echo.cd.pwd.export.unset.env.exit");
	new->builtincmds = ft_split(builtin, '.');
	new->last_return = ft_itoa(0);
	new->dollar = ft_itoa(0);
	free(builtin);
	return (new);
}

//Function initialises an empty environment variable linked list.
t_env	*new_env_list(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->size = 0;
	new->first = 0;
	new->last = 0;
	new->null = new_env_var();
	new->null->var = ft_strdup("");
	new->null->value = ft_strdup("");
	new->null->whole = ft_strdup("");
	return (new);
}

//Function initialises an empty environment variable node.
t_envvar	*new_env_var(void)
{
	t_envvar	*new;

	new = (t_envvar *)malloc(sizeof(t_envvar));
	new->index = 0;
	new->var = NULL;
	new->value = NULL;
	new->whole = NULL;
	new->prev = 0;
	new->next = 0;
	return (new);
}
