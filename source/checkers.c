/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:47:17 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/20 05:48:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mut);
	if (ft_timestamp() - philo->last_meal >= philo->data->time_to_die)
		return (pthread_mutex_unlock(&philo->meal_mut), true);
	pthread_mutex_unlock(&philo->meal_mut);
	return (false);
}

bool	is_over(t_data *data)
{
	pthread_mutex_lock(&data->mut);
	if (data->philo_died)
		return (pthread_mutex_unlock(&data->mut), true);
	pthread_mutex_unlock(&data->mut);
	return (false);
}
