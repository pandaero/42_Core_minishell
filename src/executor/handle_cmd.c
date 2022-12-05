/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:34:53 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/05 14:20:50 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int find_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
	int i;
	char *mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, minidata->env);
	while(minidata->splitpath[i])
	{
		mycmd = ft_strjoin(minidata->splitpath[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, minidata->env);
		free(mycmd);
		i++;
	}
	return (error_cmd_nf(cmd->str[0]), 127);
}

static void handle_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
	int exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	// if (builtins)
	// {
	//     exit_code = builtinsfunct;
	//     exit(exit_code);
	// }
	if (cmd->str[0][0] != '\0') // else if
		exit_code = find_cmd(cmd, minidata);
	exit(exit_code);
}

void    ft_dup_cmd(t_simple_cmds *cmd, t_minidata *minidata, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		allerrors(4, minidata);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		allerrors(4, minidata);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, minidata);
}