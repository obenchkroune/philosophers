/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 02:12:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 02:39:29 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_usleep(t_philo *philo, uint32_t ms)
{
	uint32_t	end;

	end = ft_timestamp() + ms;
	while (ft_timestamp() < end)
	{
		if (reached_required_meals(philo) || philo_died(philo))
			break ;
		usleep(500);
	}
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->data->count == 1)
	{
		print_state(philo, HAS_FORK);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, HAS_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, HAS_FORK);
	}
}

void	ft_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	print_state(philo, EATING);
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	philo->total_meals += 1;
	if (philo->total_meals == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->meals_mut);
		philo->data->max_meals_reached += 1;
		pthread_mutex_unlock(&philo->data->meals_mut);
	}
	pthread_mutex_unlock(&philo->mutex);
	smart_usleep(philo, philo->data->time_to_eat);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	smart_usleep(philo, philo->data->time_to_sleep);
}
