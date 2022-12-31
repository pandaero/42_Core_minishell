/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 19:53:42 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

//Function sets up the sigaction signal handlers
void	setup_signal(void)
{
	struct sigaction	actionint;
	struct sigaction	actionquit;

	actionint.sa_handler = &sigint;
	actionquit.sa_handler = SIG_IGN;
	sigemptyset(&actionint.sa_mask);
	sigemptyset(&actionquit.sa_mask);
	actionint.sa_flags = SA_RESTART;
	actionquit.sa_flags = 0;
	sigaddset(&actionint.sa_mask, SIGINT);
	sigaddset(&actionquit.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &actionint, 0) == -1 || \
		sigaction(SIGQUIT, &actionquit, 0) == -1)
		error_sig();
}

//Function sets up the sigaction signal handlers for the parent process.
void	setup_parent_signal(void)
{
	struct sigaction	actionint;
	struct sigaction	actionquit;

	actionint.sa_handler = SIG_IGN;
	actionquit.sa_handler = SIG_IGN;
	sigemptyset(&actionint.sa_mask);
	sigemptyset(&actionquit.sa_mask);
	actionint.sa_flags = 0;
	actionquit.sa_flags = 0;
	sigaddset(&actionint.sa_mask, SIGINT);
	sigaddset(&actionquit.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &actionint, 0) == -1 || \
		sigaction(SIGQUIT, &actionquit, 0) == -1)
		error_sig();
}

//Function sets up the sigaction signal handlers for child processes.
void	setup_child_signal(void)
{
	struct sigaction	actionint;
	struct sigaction	actionquit;

	actionint.sa_handler = &sigint_ch;
	actionquit.sa_handler = &sigqt_ch;
	sigemptyset(&actionint.sa_mask);
	sigemptyset(&actionquit.sa_mask);
	actionint.sa_flags = SA_RESTART;
	actionquit.sa_flags = 0;
	sigaddset(&actionint.sa_mask, SIGINT);
	sigaddset(&actionquit.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &actionint, 0) == -1 || \
		sigaction(SIGQUIT, &actionquit, 0) == -1)
		error_sig();
}
