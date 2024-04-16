/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:55:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/28 07:14:17 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_unsigned(const char *str)
{
	if (ft_strlen(str) > 10 || (ft_strlen(str) == 10 && \
		ft_strcmp(str, "4294967295") > 0))
		return (false);
	return (true);
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

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Invalid number of arguments\n");
		return (true);
	}
	while (av[i])
	{
		if (!is_valid_number(av[i]) || !is_valid_unsigned(av[i]))
		{
			printf("Invalid argument: %s\n", av[i]);
			return (true);
		}
		i++;
	}
	return (false);
}
