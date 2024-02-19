/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:14:53 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 23:21:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(uint32_t count)
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

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	data->philo_died = false;
	data->forks = init_forks(data->count);
	pthread_mutex_init(&data->print_mut, NULL);
	pthread_mutex_init(&data->mut, NULL);
	data->start = ft_timestamp();
	return (data);
}

void	init_philo(t_philo **philo, int ac, char **av)
{
	t_data		*data;
	uint32_t	i;

	data = init_data(ac, av);
	*philo = malloc(sizeof(t_philo) * data->count);
	if (!*philo)
		return ;
	i = 0;
	while (i < data->count)
	{
		(*philo)[i].idx = i;
		(*philo)[i].data = data;
		(*philo)[i].right = (i + 1) % data->count;
		(*philo)[i].left = i;
		pthread_mutex_init(&(*philo)[i].mut, NULL);
		i++;
	}
}
