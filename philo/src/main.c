/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:27:39 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 07:38:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philo;

	if (!check_errors(ac, av))
		return (1);
	data = init_data(ac, av);
	philo = init_philo(data);
	run_philosophers(data, philo);
	pthread_mutex_lock(&data->death_lock);
	pthread_mutex_unlock(&data->death_lock);
	// cleanup_philo(data, philo);
	return (0);
}
