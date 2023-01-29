/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:08:01 by fwong             #+#    #+#             */
/*   Updated: 2023/01/27 16:08:01 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf(RED "Only input: - number of philosophers\n");
		printf(RED "			- time to die/eat/sleep\n");
		printf(RED "			- (optionally) number of meals\n");
		return (0);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
		{
			printf(RED "Invalid options, only put nmbers please\n");
			return (1);
		}
		else if (ft_atoi(argv[i]) < 0)
		{
			printf(RED "Input positive numbers and at least 1 philosopher\n");
			return (1);
		}
		i++;
	}
	return (0);
}
