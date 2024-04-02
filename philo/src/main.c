/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 01:44:17 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/02 00:54:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	u_int32_t	i;

	if (has_errors(ac, av))
		return (1);
	philo = init_philo(ac, av);
	start_philo(philo);
	i = 0;
	while (i < philo->data->count)
		pthread_join(philo[i++].tid, NULL);
	cleanup_philo(philo);
	return (0);
}
