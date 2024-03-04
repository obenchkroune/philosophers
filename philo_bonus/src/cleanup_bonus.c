/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:35:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/01 22:37:30 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_philo(t_philo *philo, bool cleanup_mut)
{
	t_data		*data;
	uint32_t	i;

	data = philo->data;
	if (cleanup_mut)
	{
		sem_close(data->forks);
		sem_close(data->print_sem);
	}
	i = 0;
	while (i < data->count)
	{
		free(philo[i].sem_name);
		if (cleanup_mut)
			sem_close(philo[i].meal_sem);
		i++;
	}
	free(data);
	free(philo);
}
