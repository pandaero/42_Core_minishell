/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:20:41 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/09 20:52:20 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>

//Function handles an "command not found" error.
int	error_cmd_nf(char *line)
{
	write(STDERR_FILENO, "minishell: command not found: ", 30);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, "\n", 1);
	return (127);
}

//Function handles an "no permission cmd" error.
void	error_cmd_np(const char *line)
{
	char	*cnf;

	write(STDERR_FILENO, "minishell: permission denied: ", 30);
	cnf = findcommand(line);
	write(STDERR_FILENO, cnf, ft_strlen(cnf));
	write(STDERR_FILENO, "\n", 1);
	free(cnf);
}

//Function handles an error in signal action setup.
void	error_sig(void)
{
	write(STDERR_FILENO, "error: couldn't set-up signal handling", 38);
	exit(EXIT_FAILURE);
}

//Function prints out a syntax error message.
void	error_syntax(int type)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token ", 46);
	if (type == 1)
		write(STDERR_FILENO, "`|'", 3);
	else
		write(STDERR_FILENO, "`newline'", 9);
	ft_putchar_fd('\n', STDERR_FILENO);
}

//Function displays the "parser error" message.
void	parser_error(int error, t_minidata *minidata, t_word *lexer_l)
{
	free_lexer(&lexer_l);
	ft_printf("Parser error\n");
	(void) error;
	(void) minidata;
}

//Function prints out a syntax error message.
int	parser_token_error(t_minidata *minidata, t_word *lexer_l, t_token token)
{
	(void) minidata;
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESS_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	free_lexer(&lexer_l);
	return (EXIT_FAILURE);
}
