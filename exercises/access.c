#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int		ret;
	char	file[100];

	fgets(file, 100, stdin);
	ret = access(file, F_OK);
	printf("\nFile %s access: %d\n", file, ret);
	return (0);
}
