/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:35:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 23:51:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	cleanup_semaphore(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

void	cleanup_philo(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	cleanup_semaphore(data->forks, SEM_FORKS);
	cleanup_semaphore(data->print_sem, SEM_PRINT);
	cleanup_semaphore(data->sync_sem, SEM_SYNC);
	cleanup_semaphore(data->meal_sem, SEM_MEAL);
	free(data);
	free(philo);
}
