/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:52:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/19 23:13:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrfd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] && s2[i]);
}

int	ft_atoi(const char *n)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (n[i] == 32 || (n[i] >= 9 && n[i] <= 13))
		i++;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i++] == '-')
			sign *= -1;
	}
	while (n[i] >= '0' && n[i] <= '9')
	{
		result = result * 10 + (n[i] - '0');
		i++;
	}
	return (result * sign);
}

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
