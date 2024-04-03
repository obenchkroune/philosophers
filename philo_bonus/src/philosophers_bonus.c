/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:05:53 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/03 00:41:36 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_dead(t_philo *philo)
{
	sem_wait(philo->sem);
	if (philo->next_meal > ft_timestamp())
	{
		sem_post(philo->sem);
		return (false);
	}
	sem_post(philo->sem);
	return (true);
}

void	*check_death_routine(t_philo	*philo)
{
	while (!is_dead(philo))
		usleep(1000);
	print_state(philo, DEAD);
	sem_post(philo->data->stop_sem);
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, (void *)check_death_routine, philo);
	pthread_detach(tid);
	while (true)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
		print_state(philo, THINKING);
	}
}

void	start_philo(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	philo->data->start = ft_timestamp();
	while (i < philo->data->philo_count)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_routine(&philo[i]);
			exit(0);
		}
		i++;
	}
}
