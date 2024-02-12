/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:58:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 17:41:06 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	is_valid_number(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	return (true);
}

static bool	is_valid_positive_int(const char *s)
{
	if (!is_valid_number(s) || ft_strlen(s) > 10 || ft_atoi(s) < 0 || \
		(ft_strlen(s) == 10 && ft_strcmp(s, "2147483647") < 0))
		return (false);
	return (true);
}

bool	check_errors(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		write(2, "invalid number of arguments\n", 28);
		return (false);
	}
	i = 1;
	while (av[i])
	{
		if (!is_valid_positive_int(av[i]))
		{
			write(2, "invalid argument: ", 18);
			write(2, av[i], ft_strlen(av[i]));
			write(2, "\n", 1);
			return (false);
		}
		i++;
	}
	return (true);
}
