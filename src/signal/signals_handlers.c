/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 19:53:27 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <readline/readline.h>

//Function handles the SIGINT signal. Redisplay prompt.
void	sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//Function handles the SIGINT signal for the child. Take SIGINT.
void	sigint_ch(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', STDERR_FILENO);
}

//Function handles the SIGQUIT signal for the child. Take SIGQUIT.
void	sigqt_ch(int sig)
{
	(void) sig;
}
