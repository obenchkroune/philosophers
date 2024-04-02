/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:05:53 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/01 22:38:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_dead(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	if (philo->next_meal > ft_timestamp())
	{
		sem_post(philo->meal_sem);
		return (false);
	}
	return (sem_post(philo->meal_sem), true);
}

void	*check_death_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!is_dead(philo))
		usleep(500);
	print_state(philo, DEAD);
	cleanup_philo(philo - philo->idx, false);
	exit(1);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	tid;

	philo->next_meal = ft_timestamp() + philo->data->time_to_die;
	pthread_create(&tid, NULL, &check_death_routine, philo);
	while (true)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
		print_state(philo, THINKING);
	}
	pthread_join(tid, NULL);
	cleanup_philo(philo - philo->idx, false);
}

void	start_philo(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	philo->data->start = ft_timestamp();
	while (i < philo->data->count)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			philo_routine(&philo[i]);
		i++;
	}
}
