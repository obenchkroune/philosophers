/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:10:20 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/20 05:49:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, uint32_t time)
{
	long	start;
	t_data	*data;

	start = ft_timestamp();
	data = philo->data;
	while (ft_timestamp() - start < time && !is_over(data))
		usleep(500);
}

void	print_state(t_philo *philo, t_state state)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mut);
	if (!is_over(data))
	{
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
	}
	pthread_mutex_unlock(&data->print_mut);
}

void	take_forks(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->right]);
	print_state(philo, HAS_FORK);
	pthread_mutex_lock(&data->forks[philo->left]);
	print_state(philo, HAS_FORK);
}

void	put_forks(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->left]);
	pthread_mutex_unlock(&data->forks[philo->right]);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	print_state(philo, EATING);
	pthread_mutex_lock(&philo->meal_mut);
	philo->last_meal = ft_timestamp();
	pthread_mutex_unlock(&philo->meal_mut);
	usleep(1000 * data->time_to_eat);
	put_forks(philo);
}
