/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:21:13 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/23 13:29:29 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

t_simple_cmds	*call_expander(t_minidata *minidata, t_simple_cmds *cmd)
{
	t_word	*start;
	int		i;

	i = 0;
	while (cmd->str[i])
	{
		cmd->str[i] = string_expansion(minidata, cmd->str[i]);
		i++;
	}
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->str
				= string_expansion(minidata, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

int	forking(t_minidata *minidata, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i;

	if (minidata->reset == true)
	{
		i = 0;
		minidata->reset = false;
	}
	minidata->pid[i] = fork();
	if (minidata->pid[i] < 0)
		allerrors(3, minidata);
	if (minidata->pid[i] == 0)
		dup_cmd(cmd, minidata, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	pipe_wait(int *pid, int amount, t_minidata *minidata)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		update_return(minidata, WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

int	check_fd(t_minidata *minidata, int end[2], t_simple_cmds *cmd)
{
	int	fd_in;

	fd_in = 0;
	if (minidata->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	start_executor(t_minidata *minidata)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (minidata->simple_cmds)
	{
		minidata->simple_cmds = call_expander(minidata, minidata->simple_cmds);
		if (minidata->simple_cmds->next)
			pipe(end);
		if (send_heredoc(minidata, minidata->simple_cmds))
			return (EXIT_FAILURE);
		forking(minidata, end, fd_in, minidata->simple_cmds);
		close(end[1]);
		if (minidata->simple_cmds->prev)
			close(fd_in);
		fd_in = check_fd(minidata, end, minidata->simple_cmds);
		if (minidata->simple_cmds->next)
			minidata->simple_cmds = minidata->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(minidata->pid, minidata->num_pipes, minidata);
	minidata->simple_cmds = simple_cmdsfirst(minidata->simple_cmds);
	return (0);
}
