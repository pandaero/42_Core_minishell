// Tests for the functions in utils/utils_expansion_2.c
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

//*Test for clean_dquotes. cc -Wall -Werror -Wextra utils_expansion_2_main.c ../src/utils/utils_expansion_2.c ../libft/libft.a
int	main(void)
{
	char	*str1 = ft_strdup("\"hello\"there\"again\"");
	printf("%s\n", str1);
	char	*new1 = clean_dquotes(str1);
	printf("%s\n", new1);
	char	*str2 = ft_strdup("\"hello\"th\"ere\"again\"");
	printf("%s\n", str2);
	char	*new2 = clean_dquotes(str2);
	printf("%s\n", new2);
	char	*str3 = ft_strdup("\"hello\"th\"\"ere\"again\"");
	printf("%s\n", str3);
	char	*new3 = clean_dquotes(str3);
	printf("%s\n", new3);
	free(new1);
	free(new2);
	free(new3);
	return (0);
}
//*/
