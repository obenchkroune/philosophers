/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:41:50 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 17:45:57 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	do_eat(t_data *data, t_philo *philo, int right_fork)
{
	pthread_mutex_lock(data->forks[philo->idx]);
	print_status(philo, HAS_FORK);
	if (is_dead(philo, 0))
		print_status(philo, DEAD);
	if (data->philo_count > 1)
	{
		pthread_mutex_lock(data->forks[right_fork]);
		print_status(philo, HAS_FORK);
		print_status(philo, EATING);
		philo->last_meal = ft_timestamp();
		philo->total_meals++;
		pthread_mutex_lock(&data->meal_lock);
		if (philo->total_meals == data->max_meals)
			data->max_meal_reached++;
		pthread_mutex_unlock(&data->meal_lock);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(data->forks[right_fork]);
	}
	else
	{
		usleep(data->time_to_die - (ft_timestamp() - philo->last_meal));
		print_status(philo, DEAD);
	}
	pthread_mutex_unlock(data->forks[philo->idx]);
}

void	do_sleep(t_data *data, t_philo *philo)
{
	print_status(philo, SLEEPING);
	if (is_dead(philo, data->time_to_sleep))
	{
		usleep(data->time_to_die - (ft_timestamp() - philo->last_meal));
		print_status(philo, DEAD);
	}
	usleep(data->time_to_sleep);
}

bool	handle_philo_rotation(t_data *data, t_philo *philo)
{
	int	right_fork;

	right_fork = philo->idx + 1;
	if (right_fork >= data->philo_count)
		right_fork = 0;
	print_status(philo, THINKING);
	do_eat(data, philo, right_fork);
	if (is_dead(philo, 0))
		return (false);
	do_sleep(data, philo);
	return (true);
}

bool	is_dead(t_philo *philo, int extra_time)
{
	return (ft_timestamp() - philo->last_meal + extra_time >= \
		philo->data->time_to_die);
}
