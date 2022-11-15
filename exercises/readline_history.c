// Compile with -lreadline
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

//Program is a simple copycat, whatever is written is copied.
int	main(void)
{
	char	*lineread;

	lineread = (char *) 1;
	while (lineread != 0)
	{
		lineread = readline("Write: ");
		if (strlen(lineread) > 0)
			add_history(lineread);
		free(lineread);
	}
	printf("You wrote: \"%s\"\n", lineread);
	return (0);
}

