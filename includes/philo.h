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
#include <stdbool.h>

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
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				died;
	long			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*check_latest_meal;
	pthread_mutex_t	*check_max_meals;
	pthread_mutex_t	*check_death;
}	t_input;

typedef struct s_philo
{
	int					philo_id;
	int					nb_meals;
	int					latest_meal;
	pthread_t			philo_thread;
	t_input				*input;
}	t_philo;

typedef enum e_status
{
	DIED,
	THINKING,
	EATING,
	SLEEPING,
	FORK
}	t_status;

// ========================================================================= //
//                                   Prototypes                              //
// ========================================================================= //

// fork.c
void	ft_take_fork(t_philo *philo);
void	ft_put_fork(t_philo *philo);

// init.c
bool	init_input_struct(t_input *input, int argc, char **argv);
bool	init_mutexes(t_input *input);
t_philo	*init_philo_struct(t_input *input);
bool	init_threads(t_input *input, t_philo *philo);

// main.c
void	ft_actions(t_philo *philo);
void	*ft_routine(t_philo *philo);

// output.c
void	ft_write_status(t_philo *philo, t_status status);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo, long long tts);

// parsing.c
bool	ft_check_args(int argc, char **argv);

// utils.c
time_t	get_time_in_ms(void);
void	ft_destroy(t_input *input);
bool	ft_check_max_meals(t_philo *philo);
bool	ft_check_death(t_philo *philo);
void	ft_usleep(t_philo *philo, long long tts);

#endif