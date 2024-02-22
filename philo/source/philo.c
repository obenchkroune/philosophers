/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:56:03 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/22 16:23:35 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	if (data->count == 1)
	{
		print_state(philo, HAS_FORK);
		usleep(data->time_to_die * 1000);
		print_state(philo, DEAD);
		return (NULL);
	}
	if (philo->idx % 2 != 0)
		usleep(500);
	while (!is_over(data))
	{
		eat(philo);
		print_state(philo, SLEEPING);
		put_forks(philo);
		ft_usleep(philo, data->time_to_sleep);
		print_state(philo, THINKING);
	}
	return (NULL);
}

void	*monitor_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (!is_over(data) && !is_dead(philo))
		usleep(500);
	print_state(philo, DEAD);
	pthread_mutex_lock(&data->mut);
	data->philo_died = true;
	pthread_mutex_unlock(&data->mut);
	return (NULL);
}

void	run_philo(t_philo *philo)
{
	uint32_t	i;
	pthread_t	tid;

	i = 0;
	while (i < philo->data->count)
	{
		pthread_create(&tid, NULL, &monitor_routine, &philo[i]);
		pthread_detach(tid);
		pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->count)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}
