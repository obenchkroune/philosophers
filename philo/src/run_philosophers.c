/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:38:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 17:46:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (!data->finished && handle_philo_rotation(data, philo))
	{
		pthread_mutex_lock(&data->meal_lock);
		pthread_mutex_lock(&data->print_lock);
		if (data->max_meal_reached == data->philo_count)
			data->finished = true;
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_unlock(&data->meal_lock);
	}
	return (NULL);
}

void	run_philosophers(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (i % 2 == 0)
			usleep(50);
		pthread_create(&philo[i]->thread_id, NULL, &philo_routine, \
			(void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philo[i]->thread_id, NULL);
		i++;
	}
}
