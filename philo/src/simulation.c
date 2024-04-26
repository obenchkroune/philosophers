/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:50:22 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/26 21:44:56 by obenchkr         ###   ########.fr       */
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
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	pthread_t	tid;

	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	if (philo->data->count > 1)
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

void	start_simulation(t_philo *philo)
{
	uint32_t	i;
	t_data		*data;

	data = philo->data;
	i = 0;
	data->start = ft_timestamp();
	while (i < data->count)
	{
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		pthread_create(&philo[i].tid, NULL, (void *)philo_routine, &philo[i]);
		i += 1;
	}
}
