/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:50:22 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/02 01:05:36 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death_routine(void *ptr)
{
	t_philo		*philo;

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
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)ptr;
	pthread_create(&tid, NULL, &check_death_routine, philo);
	pthread_detach(tid);
	if (philo->idx % 2 != 0)
		usleep(500);
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

	i = 0;
	data = philo->data;
	data->start = ft_timestamp();
	while (i < data->count)
	{
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]);
		i++;
	}
}
