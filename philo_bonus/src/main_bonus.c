/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:46:37 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/01 00:44:59 by obenchkr         ###   ########.fr       */
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
	t_philo	*philo;
	int		status;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	if (philo->data->max_meals == 0)
		return (cleanup_philo(philo), 0);
	start_philo(philo);
	while (waitpid(-1, &status, 0) != -1 && WEXITSTATUS(status) != 1)
	{
	}
	kill_all_philo(philo);
	cleanup_philo(philo);
	return (0);
}
