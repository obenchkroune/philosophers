/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:38:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 15:42:33 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	is_going_to_die(t_philo *philo, int extra_time)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	if (data->finished)
		return (true);
	pthread_mutex_unlock(&data->print_lock);
	if (ft_timestamp() - philo->last_meal + extra_time \
		>= data->time_to_die)
	{
		usleep(data->time_to_die - (ft_timestamp() - philo->last_meal));
		pthread_mutex_lock(&data->print_lock);
		data->finished = true;
		printf("DIED\n");
		pthread_mutex_unlock(&data->print_lock);
		return (true);
	}
	return (false);
}

void	print_status(t_philo *philo, t_status status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	if (!data->finished)
	{
		printf("[%ld] %d ", ft_timestamp(), philo->idx + 1);
		if (status == THINKING)
			printf("is thinking\n");
		else if (status == HAS_FORK)
			printf("has taken a fork\n");
		else if (status == EATING)
			printf("is eating\n");
		else if (status == SLEEPING)
			printf("is sleeping\n");
	}
	pthread_mutex_unlock(&data->print_lock);
}

bool	handle_philo_rotation(t_data *data, t_philo *philo)
{
	int	right;

	right = philo->idx + 1;
	if (right >= data->philo_count)
		right = 0;
	print_status(philo, THINKING);
	pthread_mutex_lock(data->forks[right]);
	print_status(philo, HAS_FORK);
	pthread_mutex_lock(data->forks[philo->idx]);
	print_status(philo, HAS_FORK);
	print_status(philo, EATING);
	philo->last_meal = ft_timestamp();
	usleep(data->time_to_eat);
	pthread_mutex_unlock(data->forks[philo->idx]);
	pthread_mutex_unlock(data->forks[right]);
	if (is_going_to_die(philo, data->time_to_sleep))
		return (false);
	print_status(philo, SLEEPING);
	usleep(data->time_to_sleep);
	return (true);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	if (philo->idx % 2 == 0)
		usleep(100);
	while (!is_going_to_die(philo, 0))
	{
		if (!handle_philo_rotation(data, philo))
		{
			break ;
		}
	}
	return (NULL);
}

void	run_philosophers(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&philo[i]->thread_id, NULL, &philo_routine, (void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philo[i]->thread_id, NULL);
		i++;
	}
}