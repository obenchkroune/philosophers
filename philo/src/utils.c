/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 17:46:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

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
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

void	print_status(t_philo *philo, t_status status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	if (!data->finished)
	{
		printf("[%ld] %d ", ft_timestamp() / 1000, philo->idx + 1);
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
			printf("died\n");
			data->finished = true;
		}
	}
	pthread_mutex_unlock(&data->print_lock);
}
