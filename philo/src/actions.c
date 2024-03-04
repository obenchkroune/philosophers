/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 02:12:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 21:16:15 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_usleep(t_philo *philo, uint32_t ms)
{
	uint32_t	end;

	end = ft_timestamp() + ms;
	while (ft_timestamp() < end && !philo->data->philo_died)
		usleep(500);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(philo->left_fork);
	}
	print_state(philo, HAS_FORK);
}

void	ft_put_forks(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mut);
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	if (++philo->total_meals == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->meals_mut);
		philo->data->max_meals_reached++;
		pthread_mutex_unlock(&philo->data->meals_mut);
	}
	print_state(philo, EATING);
	smart_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->meal_mut);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	smart_usleep(philo, philo->data->time_to_sleep);
}
