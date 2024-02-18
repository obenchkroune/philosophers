/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 06:22:45 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 07:37:17 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philo(t_data *data, t_philo **philo)
{
	int	i;
	
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&philo[i]->lock);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meals_lock);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(data->forks[i]);
		i++;
	}
}
