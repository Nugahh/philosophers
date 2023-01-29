/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:08:01 by fwong             #+#    #+#             */
/*   Updated: 2023/01/27 16:08:01 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	r;
	int			neg;

	i = 0;
	r = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{	
		r = r * 10 + (str[i] - 48);
		i++;
	}
	if (r > INT_MAX)
		return (0);
	return (neg * r);
}

bool	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf(RED "Only input: - number of philosophers\n");
		printf(RED "			- time to die/eat/sleep\n");
		printf(RED "			- (optionally) number of meals\n");
		return (1);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
		{
			printf(RED "Input positive numbers and at least 1 philosopher\n");
			return (1);
		}
		else if (!ft_isdigit(argv[i]))
		{
			printf(RED "Invalid options, only put numbers please\n");
			return (1);
		}
		i++;
	}
	return (0);
}
