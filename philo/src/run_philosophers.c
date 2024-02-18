/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:38:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 22:40:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_timestamp() - philo->last_meal >= philo->data->time_to_die \
			&& !philo->is_eating)
		{
			print_status(philo, DEAD);
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_unlock(&philo->data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->lock);
	}
}

void	take_forks(t_philo *philo)
{
	t_data	*data;
	
	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, HAS_FORK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, HAS_FORK);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = true;
	philo->last_meal = ft_timestamp();
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&data->meals_lock);
	if (++philo->total_meals == data->max_meals)
		data->max_meals_reached++;
	pthread_mutex_unlock(&data->meals_lock);
	usleep(data->time_to_eat * 1000);
}

void	put_forks(t_philo *philo)
{
	t_data	*data;
	
	data = philo->data;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->lock);
	print_status(philo, SLEEPING);
	usleep(data->time_to_sleep * 1000);
	print_status(philo, THINKING);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	while (1)
	{
		take_forks(philo);
		put_forks(philo);
	}
	return (NULL);
}

void	run_philosophers(t_data *data, t_philo **philo)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&tid, NULL, &philo_routine, philo[i]);
		pthread_detach(tid);
		pthread_create(&tid, NULL, &check_death_routine, philo[i]);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
}
