/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:25:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 17:23:42 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(int count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	if (data->philo_count > 200 || data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || (ac == 6 && data->max_meals < 1))
		return (-1);
	data->forks = init_forks(data->philo_count);
	if (!data->forks || pthread_mutex_init(&data->print_mut, NULL) != 0
		|| pthread_mutex_init(&data->finished_mut, NULL) != 0)
		return (-1);
	data->start_time = get_time();
	return (0);
}

int	init_philos(t_philo *philo, t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_meal = get_time();
		if (pthread_mutex_init(&philo[i].lock, NULL) != 0)
			return (-1);
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}
