// Tests for the functions in utils/utils_expansion_4.c
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

//*Test for string_expansion. cc -Wall -Werror -Wextra test/utils_expansion_4_main.c src/utils/utils_expansion_4.c src/utils/utils_expansion_3.c src/utils/utils_expansion_2.c src/utils/utils_expansion.c src/builtin/builtin_echo.c src/utils/utils.c src/utils/utils_2.c src/utils/utils_env_4.c src/utils/utils_env_3.c src/utils/utils_env_2.c src/utils/utils_env.c src/main/init.c src/memory/memory.c libft/libft.a
int	main(int argc, char **argv, char **env)
{
	t_minidata	*minidata = (t_minidata *)malloc(sizeof(t_minidata));

	(void) argc;
	(void) argv;
	minidata->env_list = new_env_list();
	fill_env(minidata->env_list, env);
	minidata->last_return = ft_itoa(55);
	minidata->dollar = ft_itoa(23452);
	char	*str1 = ft_strdup("$\"US\"\"ER\"");
	printf("%s\n", str1);
	char	*new1 = string_expansion(minidata, str1);
	printf("%s\n", new1);
	char	*str2 = ft_strdup("\"\'$USER\'\"");
	printf("%s\n", str2);
	char	*new2 = string_expansion(minidata, str2);
	printf("%s\n", new2);
	char	*str3 = ft_strdup("$12p");
	printf("%s\n", str3);
	char	*new3 = string_expansion(minidata, str3);
	printf("%s\n", new3);
	free(new1);
	free(new2);
	free(new3);
	//free_env(minidata->env_list);
	free(minidata->last_return);
	free(minidata->dollar);
	free(minidata);
	return (0);
}
//*/
