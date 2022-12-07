/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:11:31 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/06 19:47:45 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
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

//Function handles the messages given by different executable exit statuses.
void	child_reports(t_minidata *minidata, int msg)
{
	ft_printf("\nminishell: ");
	if (msg == 1)
		ft_printf("exit: ");
	else if (msg == 2)
		ft_printf("interrupt: ");
	else if (msg == 3)
		ft_printf("terminate: ");
	else if (msg == 4)
		ft_printf("segmentation fault: ");
	else if (msg == 5)
		ft_printf("stopped: ");
	ft_printf("%s\n", minidata->runningcmdline);
}

//Function checks the status of a child process to return appropriate messages.
void	exit_status(t_minidata *minidata, int status)
{
	(void) minidata;
	if (WIFEXITED(status) == true)
	{
		child_reports(minidata, 1);
		update_return(minidata, WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGINT)
			child_reports(minidata, 2);
		if (WTERMSIG(status) == SIGQUIT)
			child_reports(minidata, 3);
		if (WTERMSIG(status) == SIGSEGV)
			child_reports(minidata, 4);
	}
	if (WIFSTOPPED(status) == true)
		child_reports(minidata, 5);
}

void	error_child(void)
{
	ft_putstr_fd("waitpid error\n", STDERR_FILENO);
}

int forking(t_minidata *minidata, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i;
	int			status;
	pid_t		ret;

	if (minidata->reset == true)
	{
		i = 0;
		minidata->reset = false;
	}
	minidata->pid[i] = fork();
	ft_printf("but here\n");
	if ((int) minidata->pid[i] > 0)
	{
		setup_parent_signal();
		ft_printf("there\n");
		minidata->runningcmdline = unsplit(cmd->str, ' ');
		ret = waitpid(minidata->pid[i], &status, WUNTRACED);
		if (ret == -1)
			error_child();
		exit_status(minidata, status);
	}
	if ((int) minidata->pid[i] == -1)
		allerrors(3, minidata);
	if (minidata->pid[i] == 0)
	{
		setup_child_signal();
		ft_printf("here\n");
		ft_dup_cmd(cmd, minidata, end, fd_in);
	}
	i++;
	return (EXIT_SUCCESS);
}

int ft_pipe_wait(int *pid, int amount, t_minidata *minidata)
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

int check_fd_heredoc(int end[2])//, t_simple_cmds *cmd)t_minidata *minidata, 
{
	int fd_in;

	fd_in = end[0];
	return (fd_in);
}

int	start_executor(t_minidata *minidata)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	end[0] = 0;
	end[1] = 0;
	while (minidata->simple_cmds)
	{
		// minidata->simple_cmds = ft_call_expansion(minidata, minidata->simple_cmds);
		if (minidata->simple_cmds->next)
			pipe(end);
		if (is_builtincmd(minidata->simple_cmds->str[0]) > 0)
			builtin_execution(minidata, is_builtincmd(minidata->simple_cmds->str[0]));
		else
		{
		// send_heredoc(minidata, minidata->simple_cmds);
			forking(minidata, end, fd_in, minidata->simple_cmds);
			close(end[1]);
			if (minidata->simple_cmds->prev)
				close(fd_in);
			fd_in = check_fd_heredoc(end);
			//ft_pipe_wait(minidata->pid, minidata->num_pipes, minidata);
		}
		if (minidata->simple_cmds->next)
			minidata->simple_cmds = minidata->simple_cmds->next;
		else
			break ;
	}
	minidata->simple_cmds = simple_cmdsfirst(minidata->simple_cmds);
	return (0);
}
