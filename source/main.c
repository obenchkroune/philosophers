/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:20 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 22:59:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	
	if (!check_errors(ac, av))
		return (1);
	init_philo(&philo, ac, av);
	run_philo(philo);
	cleanup_philo(philo);
	return (0);
}
