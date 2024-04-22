/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:33:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/02 00:33:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	reached_required_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_mut);
	if (philo->data->max_meals_reached == philo->data->count)
		return (pthread_mutex_unlock(&philo->data->meals_mut), true);
	return (pthread_mutex_unlock(&philo->data->meals_mut), false);
}

bool	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mut);
	if (philo->data->philo_died)
		return (pthread_mutex_unlock(&philo->data->death_mut), true);
	return (pthread_mutex_unlock(&philo->data->death_mut), false);
}
