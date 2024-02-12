/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:27:39 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 14:40:17 by obenchkr         ###   ########.fr       */
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
	return (0);
}