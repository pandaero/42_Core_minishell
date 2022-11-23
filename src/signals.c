/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/23 17:59:43 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <readline/readline.h>

//Function handles the SIGINT signal. Redisplay prompt, or send SIGINT to child.
void	sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
