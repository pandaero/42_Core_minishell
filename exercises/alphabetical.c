#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && n > i + 1)
		i++;
	if (str1[i] != str2[i] && n != 0)
		return ((unsigned char) str1[i] - (unsigned char) str2[i]);
	return (0);
}

int	main(void)
{
	int i, j, n;
	char str[100][100], temp[100];

	printf("%d\n", ft_strncmp("Pablo", "Pabloo", ft_strlen("Pabloo")));
	printf("Enter number of names: ");
	scanf("%d",&n);
	printf("Enter names in any order:\n");
	i = 0;
	while (i < n)
	{
		scanf("%s", str[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(str[i], str[j], ft_strlen(str[i])) > 0)
			{
				strcpy(temp, str[i]);
				strcpy(str[i], str[j]);
				strcpy(str[j], temp);
			}
			j++;
		}
		i++;
	}
	printf("The sorted order of names are:\n");
	i = 0;
	while (i < n)
	{
		printf("%s\n",str[i]);
		i++;
	}
}
