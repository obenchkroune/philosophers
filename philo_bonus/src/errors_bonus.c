/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:55:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 23:38:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_valid_unsigned(const char *str)
{
	return (ft_strlen(str) <= 10 \
		&& !(ft_strlen(str) == 10 && ft_strcmp(str, "4294967295") > 0));
}

static bool	is_valid_number(const char *nbr)
{
	while (*nbr)
	{
		if (*nbr > '9' || *nbr < '0')
			return (false);
		nbr++;
	}
	return (true);
}

bool	has_errors(int ac, char **av)
{
	size_t	i;

	if (ac != 5 && ac != 6)
		return (printf(ARG_COUNT_ERROR), true);
	i = 1;
	while (av[i])
	{
		if (!is_valid_number(av[i]) || !is_valid_unsigned(av[i]))
			return (printf(ARG_ERROR, av[i]), true);
		i++;
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (printf(MS_ERROR), true);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 250)
		return (printf(PHILO_COUNT_ERROR), true);
	return (false);
}
