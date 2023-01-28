/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:32:00 by fwong             #+#    #+#             */
/*   Updated: 2023/01/27 17:32:00 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_args(char **argv)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
	{
		printf(RED "Only input: - number of philosophers\n");
		printf(RED "			- time to die/eat/sleep\n");
		printf(RED "			- (optionally) number of meals\n");
		return (1);
	}
	while (argv[i])
	{
		if (!(ft_atoi(argv[1]) || ft_isdigit(argv[1])))
		{
			printf(RED "Invalid options, only put numbers please\n");
			return (1);
		}
		else if (ft_atoi(argv[1]) < 0)
		{
			printf(RED "Input positive numbers and at least 1 philosopher\n");
			return (1);
		}
		i++
	}
	return (0);
}