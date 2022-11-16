/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/16 18:17:25 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <sys/signal.h>

//Function handles the SIGINT signal.
void	sigint(int sig)
{
	ft_printf("You sent SIGINT %d, good on you. :)\n", sig);
}

//Function handles the SIGQUIT signal.
void	sigquit(int sig)
{
	ft_printf("You sent SIGQUIT %d, good on you. :)\n", sig);
}

//Function sets up the sigaction signal handlers
void	setup_signal(void)
{
	struct sigaction	actionint;
	struct sigaction	actionquit;

	actionint.sa_handler = &sigint;
	actionquit.sa_handler = &sigquit;
	sigemptyset(&actionint.sa_mask);
	sigemptyset(&actionquit.sa_mask);
	actionint.sa_flags = SA_RESTART;
	actionquit.sa_flags = SA_RESTART;
	sigaddset(&actionint.sa_mask, SIGINT);
	sigaddset(&actionquit.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &actionint, 0) == -1 || sigaction(SIGQUIT, &actionquit, 0) == -1)
		error_sig();
}
