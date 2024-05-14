/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:50:22 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/01 00:23:23 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <time.h>

void	*check_death_routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (should_continue(philo))
	{
		pthread_mutex_lock(&philo->mutex);
		if (ft_timestamp() > philo->next_meal)
		{
			pthread_mutex_unlock(&philo->mutex);
			print_state(philo, DEAD);
			pthread_mutex_lock(&philo->data->death_mut);
			philo->data->philo_died = true;
			pthread_mutex_unlock(&philo->data->death_mut);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	pthread_t	tid;

	pthread_mutex_lock(&philo->data->start_mut);
	pthread_mutex_unlock(&philo->data->start_mut);
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	pthread_create(&tid, NULL, &check_death_routine, philo);
	while (should_continue(philo))
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
		print_state(philo, THINKING);
	}
	pthread_join(tid, NULL);
	return (NULL);
}

void	start_simulation(t_philo *philo)
{
	uint32_t	i;
	t_data		*data;

	data = philo->data;
	i = 0;
	if (data->max_meals == 0)
		return ;
	pthread_mutex_lock(&data->start_mut);
	while (i < data->count)
	{
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		pthread_create(&philo[i].tid, NULL, (void *)philo_routine, &philo[i]);
		i += 1;
	}
	data->start = ft_timestamp();
	pthread_mutex_unlock(&data->start_mut);
}
