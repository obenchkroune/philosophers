/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 01:46:31 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/24 00:12:50 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ARG_COUNT_ERROR \
"Invalid number of arguments\n"
# define MS_ERROR \
"The time_to_die / time_to_sleep / time_to_eat must be > 60ms\n"
# define PHILO_COUNT_ERROR \
"The philo_count must be between 1 and 250\n"
# define ARG_ERROR \
"Invalid argument: %s\n"

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>

# define HAS_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_data
{
	bool			philo_died;
	uint32_t		start;
	uint32_t		count;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		time_to_die;
	int				max_meals;
	uint32_t		max_meals_reached;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	meals_mut;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		tid;
	int				idx;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				total_meals;
	uint32_t		next_meal;
}	t_philo;

size_t		ft_strlen(const char *str);
int			ft_atoi(const char *s);
t_philo		*init_philo(int ac, char **av);
uint32_t	ft_timestamp(void);
void		print_state(t_philo *philo, char *state);
int			ft_strcmp(const char *str1, const char *str2);

/* Actions */
void		ft_put_forks(t_philo *philo);
void		ft_take_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);

bool		has_errors(int ac, char **av);
void		start_simulation(t_philo *philo);
void		cleanup_philo(t_philo *philo);

bool		reached_required_meals(t_philo *philo);
bool		philo_died(t_philo *philo);

#endif
