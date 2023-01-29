/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:22:54 by fwong             #+#    #+#             */
/*   Updated: 2023/01/29 19:07:24 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->input->print);
	if (!ft_check_death(philo)
		&& !ft_check_max_meals(philo - (philo->philo_id -1)))
	{
		if (status == FORK)
			printf("%ld %d has taken a fork\n", \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == SLEEPING)
			printf(MAGENTA "%ld %d is sleeping\n" END, \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == THINKING)
			printf(BLUE "%ld %d is thinking\n" END, \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
		else if (status == EATING)
			printf(YELLOW "%ld %d eating\n" END, \
			get_time_in_ms() - philo->input->start_time, philo->philo_id);
	}
	else if (status == DIED
		&& !ft_check_max_meals(philo - (philo->philo_id -1)))
		printf(RED "%ld %d died\n" END, \
		get_time_in_ms() - philo->input->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->input->print);
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
		pthread_mutex_lock(&philo->input->check_latest_meal);
		philo->latest_meal = get_time_in_ms() - philo->input->start_time;
		pthread_mutex_unlock(&philo->input->check_latest_meal);
		ft_write_status(philo, EATING);
		pthread_mutex_lock(&philo->input->check_max_meals);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->input->check_max_meals);
		ft_usleep(philo, philo->input->time_to_eat * 1000);
		ft_put_fork(philo);
	}
}

void	ft_death(t_input *input, t_philo *philo)
{
	int	i;

	while (!ft_check_death(philo))
	{
		i = 0;
		while (i < input->total_philo)
		{
			pthread_mutex_lock(&philo->input->check_latest_meal);
			if ((get_time_in_ms() - \
				input->start_time - philo[i].latest_meal) >= input->time_to_die)
			{
				pthread_mutex_unlock(&philo->input->check_latest_meal);
				pthread_mutex_lock(&philo->input->check_death);
				input->died = philo->philo_id;
				pthread_mutex_unlock(&philo->input->check_death);
				ft_write_status(philo + i, DIED);
				return ;
			}
			else
				pthread_mutex_unlock(&philo->input->check_latest_meal);
			i++;
		}
	}
}
