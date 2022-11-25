// Tests for the functions in /utils/utils.c
#include "../minishell.h"
#include <stdio.h>

/*Test for split_size. cc -Wall -Werror -Wextra utils_main.c ../src/utils/utils.c ../src/memory/memory.c ../libft/libft.a
int	main(void)
{
	char	**split;
	char	str[] = "Hello,how,are,you?";

	split = ft_split(str, ',');
	printf("%s\n", str);
	printf("Size: %d\n", split_size(split));
	free_split(split);
	return (0);
}
//*/

/*Test for ft_atol. cc -Wall -Werror -Wextra utils_main.c ../src/utils/utils.c ../libft/libft.a
int	main(void)
{
	char	str[] = "7654321876543276546765456787654567654567654";

	printf("%s\n", str);
	printf("%ld\n", ft_atol(str));
	return (0);
}
//*/
