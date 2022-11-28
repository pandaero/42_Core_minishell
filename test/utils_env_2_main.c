// Tests for the functions in /utils/utils_env_2.c
#include "../minishell.h"
#include <stdio.h>

/*Test for is_env_list_ordered. cc -Wall -Werror -Wextra utils_env_2_main.c ../src/utils/utils_env_2.c ../src/utils/utils_2.c ../src/main/init.c ../src/memory/memory.c ../libft/libft.a
int	main(void)
{
	t_envvar	*curr;
	t_env		*list = new_env_list();
	t_envvar	*node1 = new_env_var();
	t_envvar	*node2 = new_env_var();
	t_envvar	*node3 = new_env_var();
	
	node1->var = ft_strdup("hello");
	node2->var = ft_strdup("helloe");
	node3->var = ft_strdup("helloo");
	add_env_var(list, node1);
	add_env_var(list, node2);
	add_env_var(list, node3);
	curr = list->first;
	while (curr != 0)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
	printf("Sorted: %d\n", is_env_list_ordered(list));
	free_env(list);
}
//*/

/*Test for env_list_order. cc -Wall -Werror -Wextra utils_env_2_main.c ../src/utils/utils_env_2.c ../src/utils/utils_2.c ../src/main/init.c ../src/memory/memory.c ../libft/libft.a
int	main(void)
{
	t_envvar	*curr;
	t_env		*list = new_env_list();
	t_envvar	*node1 = new_env_var();
	t_envvar	*node2 = new_env_var();
	t_envvar	*node3 = new_env_var();
	t_envvar	*node4 = new_env_var();
	
	node1->var = ft_strdup("helloa");
	node2->var = ft_strdup("helloc");
	node3->var = ft_strdup("hellod");
	node4->var = ft_strdup("helloa");
	node1->value = ft_strdup("hello");
	node2->value = ft_strdup("hello");
	node3->value = ft_strdup("hello");
	node4->value = ft_strdup("hello");
	node1->whole = ft_strdup("hello");
	node2->whole = ft_strdup("hello");
	node3->whole = ft_strdup("hello");
	node4->whole = ft_strdup("hello");
	add_env_var(list, node1);
	add_env_var(list, node2);
	add_env_var(list, node3);
	add_env_var(list, node4);
	env_list_order(list);
	curr = list->first;
	while (curr != 0)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
	free_env(list);
	return (0);
}
//*/

/*Test for fill_env. cc -Wall -Werror -Wextra utils_env_2_main.c ../src/utils/utils_env_2.c ../src/main/init.c ../src/memory/memory.c ../libft/libft.a
int	main(int argc, char **argv, char **env)
{
	t_env		*list = new_env_list();
	t_envvar	*curr;

	if (argc && argv)
		fill_env(list, env);
	curr = list->first;
	while (curr != 0)
	{
		printf("%s = %s\n", curr->var, curr->value);
		curr = curr->next;
	}
	free_env(list);
	return (0);
}
//*/
