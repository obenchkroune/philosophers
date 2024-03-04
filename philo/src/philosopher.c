/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:50:22 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 21:17:55 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death_routine(void *ptr)
{
	t_philo		*philo;
	u_int32_t	i;

	philo = (t_philo *)ptr;
	while (true)
	{
		if (philo->data->philo_died)
			return (NULL);
		pthread_mutex_lock(&philo->meal_mut);
		if (ft_timestamp() >= philo->next_meal)
		{
			print_state(philo, DEAD);
			philo->data->philo_died = true;
			i = 0;
			while (i < philo->data->count)
				pthread_mutex_unlock(&philo->data->forks[i++]);
			return (pthread_mutex_unlock(&philo->meal_mut), NULL);
		}
		pthread_mutex_unlock(&philo->meal_mut);
		usleep(1000);
	}
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)ptr;
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	pthread_create(&tid, NULL, &check_death_routine, philo);
	pthread_detach(tid);
	while (!philo->data->philo_died)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
		print_state(philo, THINKING);
	}
	return (NULL);
}

void	*max_meals_monitor(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (!data->philo_died)
	{
		pthread_mutex_lock(&data->meals_mut);
		if (data->max_meals_reached == data->count)
		{
			pthread_mutex_unlock(&data->meals_mut);
			data->philo_died = true;
			return (NULL);
		}
		pthread_mutex_unlock(&data->meals_mut);
		usleep(100);
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	uint32_t	i;
	t_data		*data;
	pthread_t	tid;

	i = 0;
	data = philo->data;
	data->start = ft_timestamp();
	while (i < data->count)
	{
		pthread_create(&tid, NULL, &max_meals_monitor, philo->data);
		pthread_detach(tid);
		pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]);
		i++;
	}
}
