/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:27:27 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 23:44:41 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philo(t_philo *philo)
{
	uint32_t	i;
	t_data		*data;

	data = philo->data;
	i = 0;
	while (i < data->count)
	{
		pthread_mutex_destroy(&philo[i].mut);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mut);
	pthread_mutex_destroy(&data->print_mut);
	free(data);
	free(philo);
}
