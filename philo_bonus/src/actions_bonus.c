/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:52:52 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/01 22:27:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	print_state(philo, HAS_FORK);
	sem_wait(data->forks);
	print_state(philo, HAS_FORK);
}

void	ft_put_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	sem_post(philo->meal_sem);
	philo->total_meals++;
	print_state(philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->total_meals == data->max_meals)
		exit(0);
	print_state(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}
