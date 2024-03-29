/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:47:07 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/29 22:20:13 by obenchkr         ###   ########.fr       */
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
	sem_t		*meal_sem;
}	t_philo;

void		cleanup_exit(int code, t_philo *philo);
void		cleanup_philo(t_philo *philo);
char		*ft_itoa(int n);
char		*ft_strjoin(const char *s1, const char *s2);
bool		has_errors(int ac, char **av);
int			ft_atoi(const char *s);
void		print_state(t_philo *philo, t_state state);
uint32_t	ft_timestamp(void);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
t_philo		*init_philo(int ac, char **av);
void		ft_take_forks(t_philo *philo);
void		ft_put_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		start_philo(t_philo *philo);
char		*ft_itoa(int n);

#endif