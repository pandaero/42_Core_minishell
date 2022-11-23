/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:31:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/23 20:27:15 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT "minishell $>"

//Typedef is for a struct containing critical data.
typedef struct s_minidata
{
	char	**env;
	char	*currline;
	char	**builtincmds;
}			t_minidata;

// INITIALISATION
//Function initialises the minidata.
void	init_minidata(t_minidata *minidata);

// ERROR HANDLING
//Function handles an "command not found" error.
void	error_cmd_nf(char *line);
//Function handles an error in signal action setup.
void	error_sig(void);

// MEMORY HANDLING (FREEING)
//Function frees a 2D char array made from ft_split.
void	free_split(char **charr);
//Function frees a minidata struct.
void	free_minidata(t_minidata *minidata);

// EXECUTION - BUILT-INS
//Function handles the execution of built-in commands.
void	builtin_execution(t_minidata *minidata);
//Function exits the program cleanly.
void	builtin_exit(t_minidata *minidata);
//Function prints the current working directory where the shell is acting.
void	builtin_pwd(t_minidata *minidata);
//Function writes to the current shell environment variables (not the global).
void	builtin_export(t_minidata *minidata);
//Function clears the contents of a local environment variable.
void	builtin_unset(t_minidata *minidata);
//Function prints out the environment variables.
void	builtin_env(t_minidata *minidata);
//Function changes the current directory where the shell is performing actions.
void	builtin_cd(t_minidata *minidata);
//Function writes a given string to the terminal. With/out newline.
void	builtin_echo(t_minidata *minidata);

// COMMAND LINE PARSING
//Function finds the command within a simple command line.
char	*findcommand(const char *line);

// VALIDATION
//Function checks that an input line contains valid instructions
int		validline(const char *line, t_minidata *minidata);
//Function determines whether a command is found within the path.
int		is_pathcmd(char *cmd, char **env);
//Function determines whether a command line calls a built-in command.
int		is_builtincmd(t_minidata *minidata);


// SIGNALS
//Function sets up the sigaction signal handlers
void	setup_signal(void);

#endif
