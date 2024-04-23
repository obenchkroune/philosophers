/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:46:37 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 23:16:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_philo(t_philo *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo->data->philo_count)
		kill(philo[i++].pid, SIGKILL);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	// pthread_t	tid;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	start_philo(philo);
	waitpid(-1, NULL, 0);
	kill_all_philo(philo);
	cleanup_philo(philo);
	return (0);
}
