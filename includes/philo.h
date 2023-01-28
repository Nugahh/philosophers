/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:39:04 by fwong             #+#    #+#             */
/*   Updated: 2023/01/27 16:39:04 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

# include <stdatomic.h>

# include "../libft/libft.h"

// ========================================================================= //
//                                   Colors                                  //
// ========================================================================= //

# define RED "\e[1;31m"
# define BLUE "\033[0;34m"
# define BOLDGREEN "\e[0;32m"
# define MAGENTA "\e[0;35m"
# define END "\033[0m"

// ========================================================================= //
//                                   Structures                              //
// ========================================================================= //

typedef struct s_input
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
}	t_input;

typedef struct s_philo
{
	int					philo_id;
	int					nb_meals;
	int					last_meal;
	int					is_eating;
	int					is_dead;
	long				start_time;
	pthread_t			philo;
	int					*left_fork;
	int					*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		*death;
	pthread_mutex_t		*lock;
	t_input				input;
}	t_philo;