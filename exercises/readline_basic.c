// Compile with -lreadline
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//Program is a simple copycat, whatever is written is copied.
int	main(void)
{
	char	*lineread;

	lineread = readline("Write: ");
	printf("You wrote: \"%s\"\n", lineread);
	return (0);
}

