/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:07 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/24 00:12:32 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define ARG_COUNT_ERROR \
"Invalid number of arguments\n"
# define MS_ERROR \
"The time_to_die / time_to_sleep / time_to_eat must be > 60ms\n"
# define PHILO_COUNT_ERROR \
"The philo_count must be between 1 and 250\n"
# define ARG_ERROR \
"Invalid argument: %s\n"

# define SEM_FORKS "/forks_sem"
# define SEM_PRINT "/print_sem"
# define SEM_SYNC "/sync_sem"
# define SEM_MEAL "/meal_sem"

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

# define HAS_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_data
{
	uint32_t	start;
	uint32_t	philo_count;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	int			max_meals;
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*sync_sem;
	sem_t		*meal_sem;
}	t_data;

typedef struct s_philo
{
	pid_t		pid;
	t_data		*data;
	int			idx;
	int			total_meals;
	uint32_t	next_meal;
}	t_philo;

void		init_data(t_data *data, int ac, char **av);
void		cleanup_philo(t_philo *philo);
bool		has_errors(int ac, char **av);
int			ft_atoi(const char *s);
void		print_state(t_philo *philo, char *state);
uint32_t	ft_timestamp(void);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
void		init_philo(t_philo *philo, t_data *data);
void		ft_take_forks(t_philo *philo);
void		ft_put_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		start_philo(t_philo *philo);

#endif
