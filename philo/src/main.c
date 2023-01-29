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

void	ft_actions(t_philo *philo)
{
	if (!ft_check_death(philo) && !ft_check_max_meals(philo))
		ft_eat(philo);
	if (!ft_check_death(philo) && !ft_check_max_meals(philo))
		ft_sleep(philo, philo->input->time_to_sleep * 1000);
	if (!ft_check_death(philo) && !ft_check_max_meals(philo))
		ft_think(philo);
	usleep(500);
}

void	*ft_routine(t_philo *philo)
{
	if (philo->input->total_philo == 1)
	{
		ft_write_status(philo, FORK);
		pthread_mutex_lock(&philo->input->check_death);
		philo->input->died = 1;
		pthread_mutex_unlock(&philo->input->check_death);
		usleep(philo->input->time_to_die * 1000);
		ft_write_status(philo, DIED);
		return (0);
	}
	if (philo->input->total_philo % 2)
	{
		if (philo->philo_id == philo->input->total_philo)
			ft_usleep(philo, (philo->input->time_to_eat * 1000) * 2);
		else if (philo->philo_id % 2)
			ft_usleep(philo, philo->input->time_to_eat * 1000);
	}
	else if (!(philo->input->total_philo % 2) && (philo->philo_id % 2))
		ft_usleep(philo, philo->input->time_to_eat * 1000);
	while (!ft_check_death(philo)
		&& !ft_check_max_meals(philo - (philo->philo_id - 1)))
		ft_actions(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_philo	*philo;

	if (ft_check_args(argc, argv) == 1)
		return (0);
	if (!init_input_struct(&input, argc, argv))
		return (0);
	philo = init_philo_struct(&input);
	if (!philo)
		return (ft_destroy(&input), 0);
	if (init_threads(&input, philo))
		return (0);
	return (ft_destroy(&input), free(philo), 0);
}
