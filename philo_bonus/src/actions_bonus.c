/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:52:52 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/24 00:00:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_take_forks(t_philo *philo)
{
	sem_t	*forks;
	sem_t	*meal_sem;

	forks = philo->data->forks;
	meal_sem = philo->data->meal_sem;
	sem_wait(meal_sem);
	sem_wait(forks);
	print_state(philo, HAS_FORK);
	sem_wait(forks);
	print_state(philo, HAS_FORK);
	sem_post(meal_sem);
}

void	ft_put_forks(t_philo *philo)
{
	sem_t	*forks;

	forks = philo->data->forks;
	sem_post(forks);
	sem_post(forks);
}

void	ft_eat(t_philo *philo)
{
	sem_t	*sync_sem;
	t_data	*data;

	print_state(philo, EATING);
	data = philo->data;
	sync_sem = data->sync_sem;
	sem_wait(sync_sem);
	philo->next_meal = ft_timestamp() + data->time_to_die;
	sem_post(sync_sem);
	philo->total_meals++;
	usleep(data->time_to_eat * 1000);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}
