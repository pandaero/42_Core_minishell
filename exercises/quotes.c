/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:00:33 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/19 16:06:31 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int ft_find_matching_quotes (char *line, int i, int *num_del, int del)
{
	int j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

int ft_count_quotes(char *line)
{
	int i;
	int s;
	int d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34) // 34 == "
			i += ft_find_matching_quotes(line, i, &d, 34);
		if (line[i] == 39) // 39 == '
			i += ft_find_matching_quotes(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}


int main(void)
{
	char	*line = "\"adasd";
	if (!ft_count_quotes(line))
		printf("fck sytax error!\n");
	else
		printf("WELL DONE!\n");
	return (0);
}