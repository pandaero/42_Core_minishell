/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:21:13 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/09 19:25:47 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int forking(t_minidata *minidata, int end[2], int fd_in, t_simple_cmds *cmd)
{
    static int i;
    
    if (minidata->reset == true)
    {
        i = 0;
        minidata->reset = false;
    }
    ft_printf("sacasc = %d\n", i);
    minidata->pid[i] = fork();
    if (minidata->pid[i] < 0)
        allerrors(3, minidata);
    if (minidata->pid[i] == 0)
        dup_cmd(cmd, minidata, end, fd_in);
    i++;
    return (EXIT_SUCCESS);
}
int pipe_wait(int *pid, int amount, t_minidata *minidata)
{
    int i;
    int status;

    i = 0;
    while (i < amount)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    waitpid(pid[i], &status, 0);
    if (WIFEXITED(status))
		minidata->last_return = ft_itoa(WEXITSTATUS(status));
    return (EXIT_SUCCESS);
}

int check_fd(int end[2])
{
    int fd_in;
    
    fd_in = end[0];
    return (fd_in);
}

int start_executor(t_minidata *minidata)
{
    int end[2];
    int fd_in;

    fd_in = STDIN_FILENO;
    while (minidata->simple_cmds)
    {
        ft_printf("HERE1\n");
        if (minidata->simple_cmds->next)
            pipe(end);
        ft_printf("HERE2\n");
        forking(minidata, end, fd_in, minidata->simple_cmds);
        close(end[1]);
        if (minidata->simple_cmds->prev)
            close(fd_in);
        ft_printf("HERE3\n");
        fd_in = check_fd(end);
        if (minidata->simple_cmds->next)
            minidata->simple_cmds = minidata->simple_cmds->next;
        else
            break;
        ft_printf("HERE5\n");
    }
    pipe_wait(minidata->pid, minidata->num_pipes, minidata);
    minidata->simple_cmds = simple_cmdsfirst(minidata->simple_cmds);
    ft_printf("HERE6\n");
    return (0);
}