/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:46:37 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 20:27:25 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	uint32_t	i;
	int			wstatus;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	start_philo(philo);
	waitpid(-1, &wstatus, 0);
	while (WEXITSTATUS(wstatus) == 0 && waitpid(-1, &wstatus, 0) != -1)
		usleep(1000);
	i = 0;
	while (i < philo->data->count)
		kill(philo[i++].pid, SIGTERM);
	cleanup_philo(philo);
	return (0);
}
