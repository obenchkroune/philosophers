/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:35:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/03 00:35:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_philo(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_close(philo->sem);
	sem_close(data->stop_sem);
	free(data);
	free(philo);
}
