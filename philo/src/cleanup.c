/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:19:10 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 17:23:49 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

static void	free_data(t_data *data)
{
	free_forks(data->forks, data->philo_count);
	pthread_mutex_destroy(&data->print_mut);
	pthread_mutex_destroy(&data->finished_mut);
}

static void	free_philos(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philo[i].lock);
		i++;
	}
}

void	cleanup(t_data *data, t_philo *philo)
{
	free_philos(philo, data->philo_count);
	free_data(data);
}
