/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:50:22 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 03:17:25 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death_routine(void *ptr)
{
	t_philo		*philo;
	uint32_t	next_meal;

	philo = (t_philo *)ptr;
	while (!reached_required_meals(philo) && !philo_died(philo))
	{
		pthread_mutex_lock(&philo->mutex);
		if (ft_timestamp() >= philo->next_meal)
		{
			pthread_mutex_unlock(&philo->mutex);
			print_state(philo, DEAD);
			pthread_mutex_lock(&philo->data->death_mut);
			philo->data->philo_died = true;
			pthread_mutex_unlock(&philo->data->death_mut);
			return (NULL);
		}
		next_meal = philo->next_meal;
		pthread_mutex_unlock(&philo->mutex);
		usleep((next_meal - ft_timestamp() - 1) * 1000);
	}
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->data->start_mut);
	pthread_mutex_unlock(&philo->data->start_mut);
	pthread_create(&tid, NULL, &check_death_routine, philo);
	while (!philo_died(philo) && !reached_required_meals(philo))
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

void	start_philo(t_philo *philo)
{
	uint32_t	i;
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->start_mut);
	i = 0;
	while (i < data->count)
	{
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]);
		i += 1;
	}
	data->start = ft_timestamp();
	pthread_mutex_unlock(&philo->data->start_mut);
}
