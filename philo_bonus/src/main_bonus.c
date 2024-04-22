/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:46:37 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 19:39:52 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*cleanup_philo_routine(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	sem_wait(philo->data->stop_sem);
	while (i < philo->data->philo_count)
		kill(philo[i++].pid, SIGKILL);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	tid;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	sem_wait(philo->data->stop_sem);
	start_philo(philo);
	pthread_create(&tid, NULL, (void *)cleanup_philo_routine, philo);
	while (waitpid(-1, NULL, 0) != -1)
		;
	sem_post(philo->data->stop_sem);
	pthread_join(tid, NULL);
	cleanup_philo(philo);
	return (0);
}
