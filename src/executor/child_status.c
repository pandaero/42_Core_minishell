/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:59:48 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/31 16:55:46 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <fcntl.h>

void	error_child(void)
{
	ft_putstr_fd("waitpid error\n", STDERR_FILENO);
}

//Function handles the messages given by different executable exit statuses.
void	child_reports(t_minidata *minidata, int msg)
{
	int	i;

	i = 0;
	ft_printf("minishell: ");
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
	while (minidata->simple_cmds->str[i])
	{
		ft_printf("%s ", minidata->simple_cmds->str[i]);
		i++;
	}
	ft_printf("\n");
}

//Function checks the status of a child process to return appropriate messages.
void	exit_status(t_minidata *minidata, int status)
{
	(void) minidata;
	if (WIFEXITED(status) == true)
		update_return(minidata, WEXITSTATUS(status));
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGINT)
		{
			child_reports(minidata, 2);
			update_return(minidata, 130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			child_reports(minidata, 3);
			update_return(minidata, 131);
		}
		if (WTERMSIG(status) == SIGSEGV)
		{
			child_reports(minidata, 4);
			update_return(minidata, 139);
		}
	}
	if (WIFSTOPPED(status) == true)
		child_reports(minidata, 5);
}
