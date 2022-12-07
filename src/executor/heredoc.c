/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:26:48 by zyunusov          #+#    #+#             */
/*   Updated: 2022/12/06 22:45:45 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static int	create_heredoc(t_word *heredoc, bool quotes,
	t_minidata *minidata, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (line && !minidata->stop_heredoc)
	{
		if (!ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str)) 
			&& (ft_strlen(line)) == ft_strlen(heredoc->str))
			break ;
		if (quotes == false)
			line =  var_expansion(minidata, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (minidata->stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	heredoc(t_minidata *minidata, t_word *heredoc, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes(heredoc->str, '\"');
	delete_quotes(heredoc->str, '\'');
	minidata->stop_heredoc = 0;
	minidata->in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, minidata, file_name);
	minidata->in_heredoc = 0;
	minidata->heredoc = true;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_minidata *minidata, t_simple_cmds *cmd)
{
	t_word	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = heredoc(minidata, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				minidata->last_return = "1";
				return (reset_tools(minidata));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
