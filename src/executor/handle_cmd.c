/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:31:49 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/09 17:02:04 by zyunusov         ###   ########.fr       */
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
    return(127);
}

static void handle_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
    int exit_code;
    
    exit_code = 0;
    if (cmd->str[0][0] != '\0')
        exit_code = find_cmd(cmd, minidata);
    exit(exit_code);
}

void dup_cmd(t_simple_cmds *cmd, t_minidata *minidata, int end[2], int fd_in)
{
    if (dup2(fd_in, STDIN_FILENO) < 0 && cmd->prev)
		allerrors(4, minidata);
    close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) < 0 && cmd->next)
		allerrors(4, minidata);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
    handle_cmd(cmd, minidata);
}