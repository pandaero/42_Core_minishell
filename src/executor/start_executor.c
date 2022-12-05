/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:11:31 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/05 14:19:01 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// t_simple_cmds   *call_expansion(t_minidata *minidata, t_simple_cmds *cmd)
// {
//     t_word *start;

//     cmd->str = var_expansion(minidata, cmd->str);
//     start = cmd->redirections;
//     while(cmd->redirections)
//     {
//         if (cmd->redirections->token != LESS_LESS)
//             cmd->redirections->str
//                 = var_expansion(minidata, cmd->redirections->str);
//         cmd->redirections = cmd->redirections->next;
//     }
//     cmd->redirections = start;
//     return (cmd);
// }

int forking(t_minidata *minidata, int end[2],int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (minidata->reset == true)
	{
		i = 0;
		minidata->reset = false;
	}
	minidata->pid[i] = fork();
	if (minidata->pid[i] < 0)
		allerrors(3, minidata);
	if (minidata->pid[i] == 0)
		ft_dup_cmd(cmd, minidata, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int ft_pipe_wait(int *pid, int amount,t_minidata *minidata)
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

int	start_executor(t_minidata *minidata)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (minidata->simple_cmds)
	{
		// minidata->simple_cmds = ft_call_expansion(minidata, minidata->simple_cmds);
		if (minidata->simple_cmds->next)
			pipe(end);
		// send_heredoc(minidata, minidata->simple_cmds);
		forking(minidata, end, fd_in, minidata->simple_cmds);
		close(end[1]);
		if (minidata->simple_cmds->prev)
			close(fd_in);
		// fd_in = ft_check_fd_heredoc(minidata, end, minidata->simple_cmds);
		if (minidata->simple_cmds->next)
			minidata->simple_cmds = minidata->simple_cmds->next;
		else
			break;
	}
	ft_pipe_wait(minidata->pid, minidata->num_pipes, minidata);
	minidata->simple_cmds = simple_cmdsfirst(minidata->simple_cmds);
	return (0);
}