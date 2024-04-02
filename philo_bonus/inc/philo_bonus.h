/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:07 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/02 01:43:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdint.h>
# include <sys/time.h>
# include <fcntl.h>

typedef enum e_state
{
	HAS_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_data
{
	uint32_t	start;
	uint32_t	count;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	int			max_meals;
	sem_t		*forks;
	sem_t		*print_sem;
}	t_data;

typedef struct s_philo
{
	pid_t		pid;
	t_data		*data;
	int			idx;
	int			total_meals;
	uint32_t	next_meal;
	char		*sem_name;
	sem_t		*lock;
}	t_philo;

#endif
