/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello_loop_ending.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:40:28 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 17:43:01 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	i = 0;

	while(1)
	{
		if (i == 3)
			break ;
		printf("hello\n");
		sleep(1);
		i++;
	}
	return(0);
}
