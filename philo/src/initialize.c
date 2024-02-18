/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:25:29 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 22:32:39 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	**init_forks(size_t count)
{
	pthread_mutex_t	**forks;
	size_t			i;

	forks = malloc(sizeof(pthread_mutex_t *) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (NULL);
		pthread_mutex_init(forks[i], NULL);
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
	data->philo_count = ft_atoi(av[1]);
	data->forks = init_forks(data->philo_count);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	data->max_meals_reached = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start = ft_timestamp();
	data->philo_died = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_lock(&data->death_lock);
	return (data);
}

t_philo	**init_philo(t_data *data)
{
	t_philo	**philo;
	int		i;

	philo = malloc(sizeof(t_philo *) * data->philo_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->philo_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->data = data;
		philo[i]->is_eating = false;
		philo[i]->idx = i;
		philo[i]->last_meal = ft_timestamp();
		philo[i]->total_meals = 0;
		philo[i]->left_fork = data->forks[i];
		philo[i]->right_fork = data->forks[(i + 1) % data->philo_count];
		pthread_mutex_init(&philo[i]->lock, NULL);
		i++;
	}
	return (philo);
}
