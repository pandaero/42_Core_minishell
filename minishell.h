/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:31:24 by pandalaf          #+#    #+#             */
/*   Updated: 2022/11/27 01:16:40 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT "minishell$ "

//Typedef declares a struct used to shorten an expansion function.
typedef struct s_expand
{
	char	*pre;
	char	*post;
	char	*var;
	char	*new;
	char	*newnew;
}			t_expand;

//Typedef serves to classify redirections and piping.
typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
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

//Typedef is for an environment variable.
typedef struct s_envvar
{
	int				index;
	char			*var;
	char			*value;
	char			*whole;
	struct s_envvar	*prev;
	struct s_envvar	*next;
}					t_envvar;

//Typedef is for the (doubly-linked) list of environment variables.
typedef struct s_env
{
	int			size;
	t_envvar	*first;
	t_envvar	*last;
}				t_env;

//Typedef is for a struct containing critical data.
typedef struct s_minidata
{
	t_word	*lexer_l;
	char	**env;
	t_env	*envlist;
	char	*currline;
	char	**builtincmds;
	char	**splitpath;
	char	*last_return;
	char	*dollar;
	int		num_pipes;
}			t_minidata;

// =============================== INITIALISATION ==============================
//Function initialises the minidata structure.
t_minidata	*init_minidata(char **env);
//Function initialises an empty environment variable linked list.
t_env		*new_env_list(void);
//Function initialises an empty environment variable node.
t_envvar	*new_env_var(void);

// =============================== ERROR HANDLING ==============================
//Function handles an "command not found" error.
void		error_cmd_nf(char *line);
//Function handles an error in signal action setup.
void		error_sig(void);

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

// ========================== MEMORY HANDLING (FREEING) ========================
//Function frees a 2D char array made from ft_split.
void		free_split(char **charr);
//Function frees a minidata struct.
void		free_minidata(t_minidata *minidata);
//Function frees an environment variable linked list.
void		free_env(t_env *list);

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
void		parser(t_minidata *minidata);

//Function for counting pipes
void		count_pipes(t_word *lexer_l, t_minidata *minidata);

// ================================ VALIDATION =================================
//Function checks that an input command line contains executable commands.
int			is_validcmdline(t_minidata *minidata);
//Function determines whether a command is found within the path.
int			is_pathcmd(char *cmd, t_minidata *minidata);
//Function determines whether a command line calls a built-in command.
int			is_builtincmd(t_minidata *minidata);
// Function handles an "syntax error: while quotes not closed"
int			is_valid_quotes(char *line);

// ================================== SIGNALS ==================================
//Function sets up the sigaction signal handlers.
void		setup_signal(void);

// =================================== UTILS ===================================
//Function returns the size of a ft_split-created array.
int			split_size(char **str);
//Function returns the size of a 2D char array.
int			nonsplit_size(char **str);
//Function checks whether a character is a numeric one.
int			is_numeric(char ch);
//Function checks whether a string contains a valid signed numeric declaration.
int			is_validnum(char *str);
//Function returns a long int with the value contained in the given char string.
long		ft_atol(char *str);
//Function returns a long long int with the value from the given char string.
long long	ft_atoll(char *str);
//Function compares two strings and returns the difference at the first point.
int			ft_strcmp(const char *str1, const char *str2);
//Function expands variables if present in an expression.
char		*var_expansion(t_minidata *minidata, const char *expression);
//Function expands a variable within an expression, given a starting point.
char		*expand_var(t_minidata *minidata, char *str, int i);
//Function checks whether the input character is valid for an environment var.
int			is_var(char ch);
//Function determines if there are variables present in an expression.
int			contains_variables(const char *str);

// ===================== UTILS - ENVIRONMENT VARIABLE LIST =====================
//Function gets the current working directory from the environment vector.
char		*get_cwd(char **env);
//Function gets an environment variable's value from the environment vector.
char		*get_env_var(char **env, char *var);
//Function finds the pointer to the environment variable from the list.
int			ind_env_var_indx(char **env, char *var);
//Function finds the pointer to environment variable element from the vector.
char		*find_env_var(char **env, char *var);
//Function looks for an environment variable in the linked list.
t_envvar	*find_env_var_list(t_minidata *minidata, char *var);
//Function sets an environment variable's value in the env variable list.
void		set_env_var(t_minidata *minidata, char *var, char *value);
//Function fills the environment variable list from the vector.
void		fill_env(t_env *envlist, char **env);
//Function copies a node element to a new one.
t_envvar	*env_var_cpy(t_envvar *var);
//Function adds a node to an environment variable linked list.
void		add_env_var(t_env *envlist, t_envvar *envvar);
//Function removes a node from an environment variable linked list.
void		rem_env_var(t_env *envlist, t_envvar *envvar);
//Function orders the environment variable list alphabetically.
void		env_list_order(t_env *list);
//Function adds the data from the environment vector element to the envvar node.
void		get_env_var_data(char *env_el, t_envvar *node);
//Function swaps two nodes in the environment variable list.
void		env_var_swap(t_envvar *var1, t_envvar *var2, t_env *list);
//Function determines whether the environment variable list is ordered.
int			is_env_list_ordered(t_env *list);

#endif
