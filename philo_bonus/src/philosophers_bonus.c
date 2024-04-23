/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:05:53 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 21:33:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death_routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->sem);
		if (ft_timestamp() >= philo->next_meal)
		{
			sem_post(philo->sem);
			break ;
		}
		sem_post(philo->sem);
		usleep(1000);
	}
	sem_post(philo->data->stop_sem);
	print_state(philo, DEAD);
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	tid;

	philo->next_meal = philo->data->start + philo->data->time_to_die;
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
