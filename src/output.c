/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:22:54 by fwong             #+#    #+#             */
/*   Updated: 2023/01/29 01:25:19 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(philo->input->print);
	if (!ft_check_death(philo) && !ft_check_max_meals(philo))
	{
		if (status == FORK)
			printf("%ld - Philosopher %d is eating\n", \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == SLEEPING)
			printf("%ld - Philosopher %d is sleeping\n", \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == THINKING)
			printf("%ld - Philosopher %d is thinking\n", \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == DIED)
			printf("%ld - Philosopher %d died\n", \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
	}
	else if (status == DIED)
		printf("%ld - Philosopher %d died\n", \
		get_time_in_ms() - philo->input->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->input->print);
}

void	ft_think(t_philo *philo)
{
	if (!ft_check_death(philo))
		ft_write_status(philo, THINKING);
}

void	ft_sleep(t_philo *philo, long long tts)
{
	if (!ft_check_death(philo))
	{
		ft_write_status(philo, SLEEPING);
		ft_usleep(philo, tts);
	}
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_death(philo))
	{
		ft_take_fork(philo);
		pthread_mutex_lock(philo->input->check_latest_meal);
		philo->latest_meal = get_time_in_ms() - philo->input->start_time;
		pthread_mutex_unlock(philo->input->check_latest_meal);
		ft_write_status(philo, EATING);
		pthread_mutex_lock(philo->input->check_max_meals);
		philo->nb_meals++;
		pthread_mutex_unlock(philo->input->check_max_meals);
		ft_put_fork(philo);
	}
}