/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:25:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 17:14:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

uint32_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_error(const char *str, t_data *data, t_philo *philo)
{
	cleanup(data, philo);
	printf("Error: %s\n", str);
	return (1);
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->data->finished_mut);
	if (philo->data->finished)
	{
		pthread_mutex_unlock(&philo->data->finished_mut);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finished_mut);
	pthread_mutex_lock(&philo->data->print_mut);
	printf("%-20d %d %s\n",
		get_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mut);
}
