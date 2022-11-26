/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:20:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/26 16:20:15 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function handles an "command not found" error.
void	error_cmd_nf(char *line)
{
	char	*cnf;

	write(STDERR, "minishell: command not found: ", 30);
	cnf = findcommand(line);
	write(STDERR, cnf, ft_strlen(cnf));
	write(STDERR, "\n", 1);
	free(cnf);
}

//Function handles an "no permission cmd" error.
void	error_cmd_np(const char *line)
{
	char	*cnf;

	write(STDERR, "minishell: permission denied: ", 30);
	cnf = findcommand(line);
	write(STDERR, cnf, ft_strlen(cnf));
	write(STDERR, "\n", 1);
	free(cnf);
}

//Function handles an error in signal action setup.
void	error_sig(void)
{
	write(STDERR, "error: couldn't set-up signal handling", 38);
	exit(EXIT_FAILURE);
}

//Function prints out a syntax error message.
int	parser_token_error(t_minidata *minidata, t_word *lexer_l, t_tokens token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == PIPE)
		write(STDERR, "`|'", 3);
	else
		write(STDERR, "`newline'", 9);
	ft_putchar_fd('\n', STDERR);
	lexer_clear(&lexer_l);
	return (EXIT_FAILURE);
}
