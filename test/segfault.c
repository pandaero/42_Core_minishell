/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:45:46 by pandalaf          #+#    #+#             */
/*   Updated: 2022/12/06 17:59:36 by pandalaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	main(void)
{
	memset(NULL, 1, 10);
	return (0);
}
