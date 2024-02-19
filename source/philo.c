/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:56:03 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 23:43:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_usleep(t_philo *philo, uint32_t time)
{
	long	start;
	t_data	*data;

	start = ft_timestamp();
	data = philo->data;
	while (ft_timestamp() - start < time)
	{
		pthread_mutex_lock(&data->mut);
		if (data->philo_died)
		{
			pthread_mutex_unlock(&data->mut);
			return ;
		}
		pthread_mutex_unlock(&data->mut);
		usleep(100);
	}
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->mut);
		if (data->philo_died)
		{
			pthread_mutex_unlock(&data->mut);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mut);
		take_forks(philo);
		print_state(philo, EATING);
		pthread_mutex_lock(&philo->mut);
		philo->last_meal = ft_timestamp();
		pthread_mutex_unlock(&philo->mut);
		smart_usleep(philo, data->time_to_eat);
		put_forks(philo);
		print_state(philo, SLEEPING);
		smart_usleep(philo, data->time_to_sleep);
		print_state(philo, THINKING);
	}
}

void	*monitor_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&philo->mut);
		if (ft_timestamp() - philo->last_meal >= data->time_to_die)
		{
			print_state(philo, DEAD);
			pthread_mutex_unlock(&philo->mut);
			pthread_mutex_lock(&data->mut);
			data->philo_died = true;
			pthread_mutex_unlock(&data->mut);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mut);
	}
}

void	run_philo(t_philo *philo)
{
	uint32_t	i;
	pthread_t	tid;

	i = 0;
	while (i < philo->data->count)
	{
		philo[i].last_meal = ft_timestamp();
		pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]);
		pthread_create(&tid, NULL, &monitor_routine, &philo[i]);
		pthread_detach(tid);
		i++;
	}
	i = 0;
	while (i < philo->data->count)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}
