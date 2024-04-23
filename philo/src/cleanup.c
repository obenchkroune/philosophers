/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 02:40:25 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 21:03:16 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philo(t_philo *philo)
{
	t_data		*data;
	uint32_t	i;

	data = philo->data;
	pthread_mutex_destroy(&data->print_mut);
	pthread_mutex_destroy(&data->meals_mut);
	pthread_mutex_destroy(&data->death_mut);
	i = 0;
	while (i < data->count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].mutex);
		i++;
	}
	free(data->forks);
	free(philo);
	free(data);
}
