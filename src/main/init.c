/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:08:30 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 19:06:22 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <stdbool.h>

//Function initialises the minidata.
t_minidata	*init_minidata(char **env)
{
	int			lvl;
	char		*alvl;
	char		*builtin;
	t_minidata	*new;

	new = (t_minidata *)malloc(sizeof(t_minidata));
	new->env = env;
	new->env_list = new_env_list();
	fill_env(new->env_list, env);
	working_path(new);
	lvl = ft_atoi(find_env_var_list(new, "SHLVL")->value) + 1;
	alvl = ft_itoa(lvl);
	set_env_var(new, "SHLVL", alvl);
	free(alvl);
	builtin = ft_strdup("echo.cd.pwd.export.unset.env.exit");
	new->builtincmds = ft_split(builtin, '.');
	new->last_return = ft_itoa(0);
	new->dollar = ft_itoa(0);
	new->simple_cmds = NULL;
	new->lexer_list = NULL;
	new->reset = false;
	new->pid = NULL;
	free(builtin);
	return (new);
}

//Function initialises an empty environment variable linked list.
t_env	*new_env_list(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->size = 0;
	new->null = new_env_var();
	new->first = new->null;
	new->last = new->null;
	new->first->prev = new->null;
	new->last->next = new->null;
	new->null->var = ft_strdup("");
	new->null->value = ft_strdup("");
	new->null->whole = ft_strdup("");
	new->null->prev = new->null;
	new->null->next = new->null;
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
