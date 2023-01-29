/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:31:20 by fwong             #+#    #+#             */
/*   Updated: 2023/01/29 19:06:04 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	if (philo->philo_id == 1)
	{
		pthread_mutex_lock(&philo->input->fork[philo->input->total_philo - 1]);
		pthread_mutex_lock(&philo->input->fork[philo->philo_id - 1]);
		ft_write_status(philo, FORK);
		ft_write_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->input->fork[philo->philo_id - 1]);
		pthread_mutex_lock(&philo->input->fork[philo->philo_id - 2]);
		ft_write_status(philo, FORK);
		ft_write_status(philo, FORK);
	}
}

void	ft_put_fork(t_philo *philo)
{
	if (philo->philo_id == 1)
	{
		pthread_mutex_unlock(&philo->input->fork[\
		philo->input->total_philo - 1]);
		pthread_mutex_unlock(&philo->input->fork[philo->philo_id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->input->fork[philo->philo_id - 1]);
		pthread_mutex_unlock(&philo->input->fork[philo->philo_id - 2]);
	}
}
