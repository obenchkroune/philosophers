/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 02:00:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/01 00:22:21 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(pthread_mutex_t forks[250], uint32_t count)
{
	uint32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->philo_died = false;
	data->count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	init_forks(data->forks, data->count);
	data->max_meals_reached = 0;
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	pthread_mutex_init(&data->print_mut, NULL);
	pthread_mutex_init(&data->meals_mut, NULL);
	pthread_mutex_init(&data->death_mut, NULL);
	pthread_mutex_init(&data->start_mut, NULL);
}

void	init_philo(t_data *data, t_philo philo[250])
{
	uint32_t	i;

	memset(philo, 0, sizeof(t_philo) * data->count);
	i = 0;
	while (i < data->count)
	{
		philo[i].data = data;
		philo[i].idx = i;
		philo[i].left_fork = &data->forks[(i + 1) % data->count];
		philo[i].right_fork = &data->forks[i];
		philo[i].total_meals = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
}
