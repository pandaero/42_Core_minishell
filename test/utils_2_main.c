// Tests for the functions in /utils/utils_2.c
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Test for var_expansion. cc -Wall -Werror -Wextra utils_2_main.c ../src/utils/utils_2.c ../src/utils/utils_env_2.c ../src/utils/utils_env_3.c ../src/memory/memory.c ../src/main/init.c ../libft/libft.a
int	main(int argc, char **argv, char **env)
{
	t_minidata	*minidata = (t_minidata *)malloc(sizeof(t_minidata));
	char		*expr = ft_strdup("hello/$HOME/here/$HOME/again");
	char		*expanded;

	if (argc && argv)
		minidata->envlist = new_env_list();
	fill_env(minidata->envlist, env);
	minidata->last_return = ft_itoa(55);
	minidata->dollar = ft_itoa(23452);
	printf("Before: %s\n", expr);
	expanded = var_expansion(minidata, expr);
	free(expr);
	printf("After:  %s\n", expanded);
	free_env(minidata->envlist);
	free(minidata->last_return);
	free(minidata->dollar);
	free(expanded);
	free(minidata);
	return (0);
}
//*/

/*Test for expand_var. cc -Wall -Werror -Wextra utils_2_main.c ../src/utils/utils_2.c ../src/utils/utils_env_2.c ../src/utils/utils_env_3.c ../src/memory/memory.c ../src/main/init.c ../libft/libft.a
int	main(int argc, char **argv, char **env)
{
	t_minidata	*minidata = (t_minidata *)malloc(sizeof(t_minidata));
	char		*expr = ft_strdup("hello$HOME/here");
	char		*expanded;

	if (argc && argv)
		minidata->envlist = new_env_list();
	fill_env(minidata->envlist, env);
	minidata->last_return = ft_itoa(55);
	minidata->dollar = ft_itoa(23452);
	printf("Before: %s\n", expr);
	expanded = expand_var(minidata, expr, 5);
	printf("After:  %s\n", expanded);
	free_env(minidata->envlist);
	free(minidata->last_return);
	free(minidata->dollar);
	free(expanded);
	free(expr);
	free(minidata);
	return (0);
}
//*/

/*Test for is_var. cc -Wall -Werror -Wextra utils_2_main.c ../src/utils/utils_2.c ../libft/libft.a
int	main(void)
{
	printf("%c, %d. %c, %d. %c, %d. %c, %d.\n", 'X', is_var('X'), 'x', is_var('x'), '5', is_var('5'), '_', is_var('_'));
	return (0);
}
//*/
