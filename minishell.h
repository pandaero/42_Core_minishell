/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:31:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/28 16:56:10 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdbool.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT "minishell$ "

//Typedef serves to classify redirections and piping.
typedef enum s_tokens
{
	PIPE = 1,
	GREAT = 2,
	GREAT_GREAT = 3,
	LESS = 4,
	LESS_LESS = 5,
}	t_tokens;

//Typedef(doubly linked list) for words(cmds).
typedef struct s_word
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_word	*next;
	struct s_word	*prev;
}					t_word;

//Typedef is for a struct containing critical data.
typedef struct s_minidata
{
	t_word	*lexer_l;
	char	**env;
	char	*currline;
	char	**builtincmds;
	char	**splitpath;
	int		num_pipes;
	bool	reset;
}			t_minidata;


int reset_tools(t_minidata *minidata);

int	main_loop(t_minidata *minidata);

// =============================== INITIALISATION ==============================
//Function initialises the minidata structure.
void		init_minidata(t_minidata *minidata);

// =============================== ERROR HANDLING ==============================
//Function handles an "command not found" error.
void		error_cmd_nf(char *line);
//Function handles an error in signal action setup.
void		error_sig(void);
//Function prints out a syntax error message.
int	parser_token_error(t_minidata *minidata, t_word *lexer_l, t_tokens token);

int allerrors(int error, t_minidata *minidata);

void	parser_error(int error, t_minidata *minidata, t_word *lexer_l);

// =================================== LEXER ===================================
// Function to read from string, to divide to tokens
int			ft_read_token(t_minidata *minidata);
// Function to read(skip) quotes
int			ft_handle_quotes(int i, char *s, char del);
// Function to put all tokens in separate container(doubly linked list)
int			add_unitto_lexer(char *s, t_tokens token, t_word **lexer_l);
// Function that check for pipe and redir only <> returns name of token
t_tokens	check_token(int c);
// Function that passes to lexer_init - pipes and redirections
int			handle_token(int i, char *s, t_word **lexer_l);
// need to write function delone, clear to free list ==== ----
void	lexerclear(t_word **lst);
void	lexerdelone(t_word **lst, int key);

// ========================== MEMORY HANDLING (FREEING) ========================
//Function frees a 2D char array made from ft_split.
void		free_split(char **charr);
//Function frees a minidata struct.
void		free_minidata(t_minidata *minidata);

// ============================ EXECUTION - BUILT-INS ==========================
//Function handles the execution of built-in commands.
void		builtin_execution(t_minidata *minidata);
//Function exits the program cleanly.
void		builtin_exit(t_minidata *minidata);
//Function prints the current working directory where the shell is acting.
void		builtin_pwd(t_minidata *minidata);
//Function writes to the current shell environment variables (not the global).
void		builtin_export(t_minidata *minidata);
//Function clears the contents of a local environment variable.
void		builtin_unset(t_minidata *minidata);
//Function prints out the environment variables.
void		builtin_env(t_minidata *minidata);
//Function changes the current directory where the shell is performing actions.
void		builtin_cd(t_minidata *minidata);
//Function writes a given string to the terminal. With/out newline.
void		builtin_echo(t_minidata *minidata);

// ============================ COMMAND LINE PARSING ===========================
//Function finds the command within a simple command line.
char		*findcommand(const char *line);

// Function that will start parsing
int			start_parser(t_minidata *minidata);
//Function performs the parsing of a command line.
int		parser(t_minidata *minidata);

//Function for counting pipes
void		count_pipes(t_word *lexer_l, t_minidata *minidata);

// ================================ VALIDATION =================================
//Function checks that an input line contains valid instructions
int			is_validline(t_minidata *minidata);
//Function determines whether a command is found within the path.
int			is_pathcmd(char *cmd, t_minidata *minidata);
//Function determines whether a command line calls a built-in command.
int			is_builtincmd(t_minidata *minidata);
// Function handles an "syntax error: while quotes not closed"
int			is_valid_quotes(char *line);

// ================================== SIGNALS ==================================
//Function sets up the sigaction signal handlers
void		setup_signal(void);

// =================================== UTILS ===================================
//Function returns the size of a ft_split-created array.
int			split_size(char **str);
//Function checks whether a character is a numeric one.
int			is_numeric(char ch);
//Function checks whether a string contains a valid signed numeric declaration.
int			is_validnum(char *str);
//Function returns a long int with the value contained in the given char string.
long		ft_atol(char *str);
//Function returns a long long int with the value from the given char string.
long long	ft_atoll(char *str);

#endif
