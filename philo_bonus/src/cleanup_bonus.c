/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:35:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 17:45:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_philo(t_philo *philo)
{
	t_data		*data;
	uint32_t	i;

	data = philo->data;
	sem_close(data->forks);
	sem_close(data->print_sem);
	i = 0;
	while (i < data->count)
	{
		free(philo[i].sem_name);
		sem_close(philo[i].meal_sem);
		i++;
	}
	free(data);
	free(philo);
}
