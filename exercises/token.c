#include <stdio.h>

int    ft_is_space(char c)
{
  return (c == ' ' || (c > 8 && c < 14));
}

int ft_spaces_skip(char *line, int i)
{
    int j;

    j = 0;
    while (ft_is_space(line[i + j]))
        j++;
    return (j);
}
int ft_handle_quotes(int i, char *s, char del)
{
    int j;
    
    j = 0;
    if (s[i + j] == del)
    {
        j++;
        while(s[i + j] != del && s[i + j] != '\0')
            j++;
        j++;
    }
    return (j);
}

static int ft_read_words(int i, char *s)
{
    int j;

    j = 0;
    while (s[i + j])
    {
        j += ft_handle_quotes(i + j, s, 34);
        j += ft_handle_quotes(i + j, s, 39);
        if (ft_is_space(s[i + j]))
            break ;
        else
            j++;    
    }
    return (j);
}

int ft_read_token(char *line)
{
    int i;
    int j;
    
    i = 0;
    while (line[i])
    {
        j = 0;
        i += ft_spaces_skip(line, i);
        if (line[i] == '>' || line[i] == '|')
            j += 1;
        else
          j = ft_read_words(i, line);
        if (j < 0)
          return (0);
        i += j;
        printf("WORDS CHARS: %d\n", j);
    }
    return (1);
}

int main(void)
{
    char *k = "pwd >file | echo Hello";
    printf("%d", ft_read_token(k));
    return(0);
}