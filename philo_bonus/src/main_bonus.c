/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:46:37 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/03 00:39:35 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	uint32_t	i;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	sem_wait(philo->data->stop_sem);
	start_philo(philo);
	sem_wait(philo->data->stop_sem);
	i = 0;
	while (i < philo->data->philo_count)
		kill(philo[i++].pid, SIGKILL);
	cleanup_philo(philo);
	return (0);
}