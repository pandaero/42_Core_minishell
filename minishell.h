#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// ERROR HANDLING
//Function handles an "command not found" error.
void	error_cmd_nf(const char *line);
//Function handles an error in signal action setup.
void	error_sig(void);

// MEMORY HANDLING

// EXECUTION

// COMMAND LINE PARSING
//Function finds the command within a simple command line.
char	*findcommand(const char *line);

// VALIDATION
//Function checks that an input line contains valid instructions
int		validline(const char *str);

// SIGNALS
//Function sets up the sigaction signal handlers
void	setup_signal(void);

#endif
