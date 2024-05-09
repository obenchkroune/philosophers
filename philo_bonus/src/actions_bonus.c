/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:52:52 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/01 00:45:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(uint32_t ms)
{
	uint32_t	end;

	end = ft_timestamp() + ms;
	while (end > ft_timestamp())
		usleep(100);
}

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
	if (philo->total_meals == philo->data->max_meals)
		exit(0);
}

void	ft_eat(t_philo *philo)
{
	print_state(philo, EATING);
	philo->total_meals++;
	sem_wait(philo->data->sync_sem);
	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	sem_post(philo->data->sync_sem);
	ft_usleep(philo->data->time_to_eat);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}
