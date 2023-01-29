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

bool	init_input_struct(t_input *input, int argc, char **argv)
{
	input->total_philo = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	input->died = 0;
	input->start_time = get_time_in_ms();
	if (argc == 6)
	{
		input->max_meals = ft_atoi(argv[5]);
		if (input->max_meals <= 0)
			return (0);
	}
	else
		input->max_meals = -1;
	input->fork = malloc(sizeof(pthread_mutex_t) * input->total_philo);
	if (!input->fork)
		return (0);
	if (!init_mutexes(input))
		return (ft_destroy(input), 0);
	return (1);
}

bool	init_mutexes(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->total_philo)
	{
		if (pthread_mutex_init(&input->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&input->print, NULL))
		return (0);
	if (pthread_mutex_init(&input->check_max_meals, NULL))
		return (0);
	if (pthread_mutex_init(&input->check_death, NULL))
		return (0);
	if (pthread_mutex_init(&input->check_latest_meal, NULL))
		return (0);
	return (1);
}

t_philo	*init_philo_struct(t_input *input)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * input->total_philo);
	if (!philo)
		return (0);
	while (i < input->total_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].input = input;
		philo[i].nb_meals = 0;
		philo[i].latest_meal = 0;
		i++;
	}
	return (philo);
}

bool	init_threads(t_input *input, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < input->total_philo)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, \
		(void *)&ft_routine, philo + i))
			return (0);
		i++;
	}
	i = 0;
	usleep(50);
	ft_death(input, philo);
	while (i < input->total_philo)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			return (0);
		i++;
	}
	ft_destroy(input);
	free(philo);
	return (1);
}
