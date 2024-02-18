/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 07:32:32 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
		sign *= -1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int				i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, t_status status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	if (!data->philo_died)
	{
		pthread_mutex_lock(&data->meals_lock);
		if (data->max_meals_reached == data->philo_count)
		{
			pthread_mutex_unlock(&data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->meals_lock);
		printf("%-19ld %d ", ft_timestamp() - data->start, philo->idx + 1);
		if (status == THINKING)
			printf("is thinking\n");
		else if (status == HAS_FORK)
			printf("has taken a fork\n");
		else if (status == EATING)
			printf("is eating\n");
		else if (status == SLEEPING)
			printf("is sleeping\n");
		else if (status == DEAD)
		{
			data->philo_died = 1;
			printf("died\n");
		}
	}
	pthread_mutex_unlock(&data->print_lock);
}
