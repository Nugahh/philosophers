/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:37:14 by fwong             #+#    #+#             */
/*   Updated: 2023/01/27 16:37:14 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initstruct(t_philo *philo, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].philo_id = i + 1;
		philo[i].input.nb_philo = ft_atoi(av[1]);
		philo[i].input.time_to_die = ft_atoi(av[2]);
		philo[i].input.time_to_eat = ft_atoi(av[3]);
		philo[i].input.time_to_sleep = ft_atoi(av[4]);
		philo[i].nb_meals = 0;
		philo[i].is_eating = 0;
		philo[i].last_meal = 0;
		philo[i].start_time = timer();
		if (argc == 6)
			philo[i].num_meals = ft_atoi(av[5]);
		i++;
	}
}