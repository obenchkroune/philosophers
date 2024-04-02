/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:55:41 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/28 09:53:37 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_valid_unsigned(const char *str)
{
	size_t	i;

	if (ft_strlen(str) > 10 || (ft_strlen(str) == 10 && \
		ft_strcmp(str, "4294967295") > 0))
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	has_errors(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error\n");
		return (true);
	}
	while (*++av)
	{
		if (!is_valid_unsigned(*av))
		{
			printf("invalid argument: %s\n", *av);
			return (true);
		}
	}
	return (false);
}
