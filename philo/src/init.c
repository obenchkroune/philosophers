/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 02:00:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 01:37:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(uint32_t count)
{
	pthread_mutex_t	*forks;
	uint32_t		i;

	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->philo_died = false;
	data->count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->forks = init_forks(data->count);
	data->max_meals_reached = 0;
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	pthread_mutex_init(&data->print_mut, NULL);
	pthread_mutex_init(&data->meals_mut, NULL);
	pthread_mutex_init(&data->death_mut, NULL);
	pthread_mutex_init(&data->start_mut, NULL);
	return (data);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;
	uint32_t	i;

	data = init_data(ac, av);
	if (!data)
		return (NULL);
	philo = malloc(sizeof(t_philo) * data->count);
	if (!philo)
	{
		free(data);
		return (NULL);
	}
	memset(philo, 0, sizeof(t_philo) * data->count);
	i = 0;
	while (i < data->count)
	{
		philo[i].data = data;
		philo[i].idx = i;
		philo[i].left_fork = &data->forks[(i + 1) % data->count];
		philo[i].right_fork = &data->forks[i];
		philo[i].total_meals = 0;
		pthread_mutex_init(&philo[i++].mutex, NULL);
	}
	return (philo);
}
