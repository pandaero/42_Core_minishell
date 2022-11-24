/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:31:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/21 07:35:19 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT "minishell $>"

//Typedef serves to classify redirections and piping.
typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
} 	t_tokens;

//Typedef(doubly linked list) for words(cmds).
typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int 			i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

//Typedef is for a struct containing critical data.
typedef struct s_minidata
{
	t_lexer	*lexer_l;
	char	*args;
	char	**env;
	char	**builtincmds;
	char	**splitpath;
}			t_minidata;


// INITIALISATION
//Function initialises the minidata.
void	init_minidata(t_minidata *minidata);

// ERROR HANDLING
//Function handles an "command not found" error.
void	error_cmd_nf(char *line);
// Function handles an "syntax error: while quotes not closed"
int ft_count_quotes(char *line);

// =========== LEXER ======================================
// Function to read from string, to divide to tokens
int ft_read_token(t_minidata *minidata);
// Function to read(skip) quotes
int ft_handle_quotes(int i, char *s, char del);
// Function to put all tokens in separate container(doubly linked list)
int add_unitto_lexer(char *s,  t_tokens token, t_lexer **lexer_l);
// Function that check for pipe and redir only <> returns name of token
t_tokens check_token(int c);
// Function that passes to lexer_init - pipes and redirections
int handle_token(int i, char *s, t_lexer **lexer_l);
// need to write function delone, clear to free list ==== ----


//Function handles an error in signal action setup.
void	error_sig(void);

// MEMORY HANDLING (FREEING)
//Function frees a 2D char array made from ft_split.
void	free_split(char **charr);
//Function frees a minidata struct.
void	free_minidata(t_minidata *minidata);

// EXECUTION

// COMMAND LINE PARSING
//Function finds the command within a simple command line.
char	*findcommand(const char *line);

// VALIDATION
//Function checks that an input line contains valid instructions
int		validline(t_minidata *minidata);
//Function determines whether a command is found within the path.
int		is_pathcmd(char *cmd, t_minidata *minidata);

// SIGNALS
//Function sets up the sigaction signal handlers
void	setup_signal(void);



#endif
