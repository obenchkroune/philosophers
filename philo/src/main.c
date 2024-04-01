/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:11:40 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 16:45:24 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo[200];

	memset(&data, 0, sizeof(t_data));
	memset(philo, 0, sizeof(t_philo) * 200);
	if (ac != 5 && ac != 6)
		return (ft_error("Wrong number of arguments", &data, philo));
	if (init_data(&data, ac, av) == -1)
		return (ft_error("Invalid arguments", &data, philo));
	if (init_philos(philo, &data) == -1)
		return (ft_error("Failed to initialize philosophers", &data, philo));
	if (start_simulation(philo) == -1)
		return (ft_error("Failed to start simulation", &data, philo));
	cleanup(&data, philo);
	return (0);
}
