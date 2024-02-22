/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:15:54 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/22 19:58:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>
#include <sys/time.h>

#define PHILO_COUNT 5
#define TIME_TO_DIE 800
#define TIME_TO_EAT 200
#define TIME_TO_SLEEP 200

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	main(void)
{
	sem_unlink("/forks");
	sem_t	*sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, PHILO_COUNT);
	if (sem == SEM_FAILED)
	{
		perror("");
		return (1);
	}
	
	long start = ft_timestamp();
	for (int i = 0; i < PHILO_COUNT; i++) {
		pid_t	pid = fork();
		if (pid == 0) {
			
			while (1)
			{
				sem_wait(sem);
				printf("%-20ld %d has taken a fork\n", ft_timestamp() - start, i + 1);
				sem_wait(sem);
				printf("%-20ld %d has taken a fork\n", ft_timestamp() - start, i + 1);
				printf("%-20ld %d is eating\n", ft_timestamp() - start, i + 1);
				usleep(TIME_TO_EAT * 1000);
				sem_post(sem);
				sem_post(sem);
				printf("%-20ld %d is sleeping\n", ft_timestamp() - start, i + 1);
				usleep(TIME_TO_SLEEP * 1000);
				printf("%-20ld %d is thinking\n", ft_timestamp() - start, i + 1);
			}
			exit(0);
		}
	}
	while (wait(NULL) != -1)
		usleep(1000);
	sem_close(sem);
	sem_unlink("/forks");
	return (0);
}
