/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:46:53 by fwong             #+#    #+#             */
/*   Updated: 2023/01/29 19:07:39 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_destroy(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->total_philo)
	{
		pthread_mutex_destroy(&input->fork[i]);
		i++;
	}
	free(input->fork);
	pthread_mutex_destroy(&input->print);
	pthread_mutex_destroy(&input->check_latest_meal);
	pthread_mutex_destroy(&input->check_max_meals);
	pthread_mutex_destroy(&input->check_death);
}

bool	ft_check_max_meals(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->input->check_max_meals);
	if (philo->input->max_meals == -1)
	{
		pthread_mutex_unlock(&philo->input->check_max_meals);
		return (0);
	}
	while (i < philo->input->total_philo)
	{
		if (philo[i].nb_meals < philo->input->max_meals)
		{
			pthread_mutex_unlock(&philo->input->check_max_meals);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->input->check_max_meals);
	return (1);
}

bool	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->check_death);
	if (!philo->input->died)
	{
		pthread_mutex_unlock(&philo->input->check_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->input->check_death);
	return (1);
}

void	ft_usleep(t_philo *philo, long long tts)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while (((get_time_in_ms() - start_time) * 1000) < tts
		&& !ft_check_death(philo)
		&& !ft_check_max_meals(philo - (philo->philo_id - 1)))
		usleep(50);
}
