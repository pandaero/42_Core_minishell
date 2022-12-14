/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:00:33 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/31 16:54:46 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	find_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, minidata->env);
	while (minidata->splitpath[i])
	{
		mycmd = ft_strjoin(minidata->splitpath[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, minidata->env);
		free(mycmd);
		i++;
	}
	return (error_cmd_nf(cmd->str[0]));
}

static void	handle_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
	{
		if (check_redirections(cmd))
			exit(1);
	}
	if (check_cmds(minidata->simple_cmds->str[0]))
		exit(0);
	if (is_builtincmd(minidata->simple_cmds->str[0]) > 0)
	{
		builtin_execution(minidata, \
						is_builtincmd(minidata->simple_cmds->str[0]));
		exit(ft_atoi(minidata->last_return));
	}
	else if (cmd->str[0][0] != '\0')
	{
		exit_code = find_cmd(cmd, minidata);
	}
	exit(exit_code);
}

void	dup_cmd(t_simple_cmds *cmd, t_minidata *minidata, int end[2], int fd_in)
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

static void	single_wait(t_minidata *minidata, int pid)
{
	pid_t	ret;
	int		status;

	setup_parent_signal();
	ret = waitpid(pid, &status, WUNTRACED);
	if (ret == -1)
		error_child();
	exit_status(minidata, status);
}

void	single_cmd(t_simple_cmds *cmd, t_minidata *minidata)
{
	int	pid;
	int	status;
	int	builtins;

	builtins = 0;
	minidata->simple_cmds = call_expander(minidata, minidata->simple_cmds);
	if (minidata->simple_cmds->str[0])
		builtins = is_builtincmd(minidata->simple_cmds->str[0]);
	if (builtins > 0 && builtins <= 4)
	{
		builtin_execution(minidata, \
							is_builtincmd(minidata->simple_cmds->str[0]));
		return ;
	}
	if (send_heredoc(minidata, cmd))
		return ;
	pid = fork();
	if (pid > 0)
		single_wait(minidata, pid);
	if (pid < 0)
		allerrors(5, minidata);
	if (pid == 0)
		handle_cmd(cmd, minidata);
	waitpid(pid, &status, 0);
}
