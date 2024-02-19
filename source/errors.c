/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:45:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 22:31:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>
#include <unistd.h>

#define USAGE "usage: ./philo \n<number_of_philosophers> \n<time_to_die> \n<time_to_eat> \
\n<time_to_sleep> \n[optional:number_of_times_each_philosopher_must_eat]\n"

/*
 * Check if the argument is a valid number / uint32 aka unsigned int
*/
static bool	is_valid_arg(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	if (ft_strlen(str) > 10 || \
		(ft_strlen(str) == 10 && ft_strcmp(str, "4294967295") > 0))
		return (false);
	return (true);
}

bool	check_errors(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstrfd(USAGE, STDERR_FILENO);
		return (false);
	}
	while (*++av)
	{
		if (!is_valid_arg(*av))
		{
			ft_putstrfd("invalid argument", STDERR_FILENO);
			ft_putstrfd(*av, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
			return (false);
		}
	}
	return (true);
}
