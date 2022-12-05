/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/05 17:13:36 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <readline/readline.h>

//Function handles the SIGINT signal. Redisplay prompt.
static void	sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//Function handles the SIGINT signal for the child. Send SIGINT to PID.
static void	sigint_ch(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', STDERR_FILENO);
}

//Function handles the SIGQUIT signal for the child.
static void	sigqt_ch(int sig)
{
	(void) sig;
	ft_putstr_fd("Stopped: \n", STDERR_FILENO);
}

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
