/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:55:39 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 22:04:16 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->data->finished_mut);
		philo->data->finished = 1;
		pthread_mutex_unlock(&philo->data->finished_mut);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->max_meals_mut);
		if (philo->data->max_meals != -1
			&& philo->data->max_meals_reached >= philo->data->philo_count)
		{
			pthread_mutex_unlock(&philo->data->max_meals_mut);
			pthread_mutex_lock(&philo->data->finished_mut);
			philo->data->finished = 1;
			pthread_mutex_unlock(&philo->data->finished_mut);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->max_meals_mut);
		pthread_mutex_lock(&philo->data->finished_mut);
		if (philo->data->finished)
			return (pthread_mutex_unlock(&philo->data->finished_mut), NULL);
		pthread_mutex_unlock(&philo->data->finished_mut);
		if (check_is_dead(philo) == 1)
			return (NULL);
		usleep(1000);
	}
}

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)arg;
	if (pthread_create(&tid, NULL, monitor_routine, philo) != 0)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->data->finished_mut);
		if (philo->data->finished)
		{
			pthread_mutex_unlock(&philo->data->finished_mut);
			break ;
		}
		pthread_mutex_unlock(&philo->data->finished_mut);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	pthread_join(tid, NULL);
	return (NULL);
}

static void	join_threads(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo->data->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo->data->philo_count)
	{
		if (pthread_create(
				&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
			return (-1);
		i++;
	}
	join_threads(philo);
	return (0);
}
