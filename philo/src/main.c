/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 01:44:17 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 23:40:32 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[250];
	uint32_t	i;

	if (has_errors(ac, av))
		return (1);
	init_data(&data, ac, av);
	init_philo(&data, philo);
	start_simulation(philo);
	i = 0;
	while (i < philo->data->count)
		pthread_join(philo[i++].tid, NULL);
	cleanup_philo(philo);
	return (0);
}
