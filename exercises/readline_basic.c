// Compile with -lreadline
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

//Program is a simple copycat, whatever is written is copied.
int	main(void)
{
	char	*lineread;

	lineread = readline("Write: ");
	printf("You wrote: \"%s\"\n", lineread);
	free(lineread);
	return (0);
}

