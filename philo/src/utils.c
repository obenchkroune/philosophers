/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 01:52:24 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 22:56:42 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (s[i] == 32 && (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print_state(t_philo *philo, t_state state)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->print_mut);
	if (!philo->data->philo_died)
	{
		printf("%-10u %d ", ft_timestamp() - data->start, philo->idx + 1);
		if (state == HAS_FORK)
			printf("has taken a fork\n");
		else if (state == EATING)
			printf("is eating\n");
		else if (state == SLEEPING)
			printf("is sleeping\n");
		else if (state == THINKING)
			printf("is thinking\n");
		else if (state == DEAD)
			printf("died\n");
	}
	pthread_mutex_unlock(&philo->data->print_mut);
}

uint32_t	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
