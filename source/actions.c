/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:10:20 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 23:42:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, t_state state)
{
	t_data	*data;
	
	data = philo->data;
	pthread_mutex_lock(&data->mut);
	if (data->philo_died)
	{
		pthread_mutex_unlock(&data->mut);
		return ;
	}
	pthread_mutex_unlock(&data->mut);
	pthread_mutex_lock(&data->print_mut);
	printf("%-20ld %d ", ft_timestamp() - data->start, philo->idx + 1);
	if (state == HAS_FORK)
		printf("has taken a fork\n");
	else if (state == EATING)
		printf("is eating\n");
	else if (state == SLEEPING)
		printf("is sleeping\n");
	else if (state == THINKING)
		printf("is thinking\n");
	else if (state == DEAD)
		printf("died\n");
	pthread_mutex_unlock(&data->print_mut);
}

void	take_forks(t_philo *philo)
{
	t_data		*data;
	
	data = philo->data;
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->right]);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(&data->forks[philo->left]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		print_state(philo, HAS_FORK);
		pthread_mutex_lock(&data->forks[philo->right]);
	}
	print_state(philo, HAS_FORK);
}

void	put_forks(t_philo *philo)
{
	t_data		*data;
	
	data = philo->data;
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->left]);
		pthread_mutex_unlock(&data->forks[philo->right]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->right]);
		pthread_mutex_unlock(&data->forks[philo->left]);
	}
}
