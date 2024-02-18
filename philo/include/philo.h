/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:03 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/18 07:40:09 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	HAS_FORK
};

struct s_data
{
	long			start;
	int				philo_count;
	int				max_meals;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meals_lock;
	int				max_meals_reached;
	int				philo_died;
};

// TODO: add status
struct s_philo
{
	t_data			*data;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				idx;
	long			last_meal;
	int				total_meals;
};

void	cleanup_philo(t_data *data, t_philo **philo);
int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
bool	check_errors(int ac, char **av);
int		ft_strcmp(const char *str1, const char *str2);
t_data	*init_data(int ac, char **av);
t_philo	**init_philo(t_data *data);
long	ft_timestamp(void);
void	run_philosophers(t_data *data, t_philo **philo);
void	print_status(t_philo *philo, t_status status);
bool	handle_philo_rotation(t_data *data, t_philo *philo);
void	do_sleep(t_data *data, t_philo *philo);
void	do_eat(t_data *data, t_philo *philo, int right_fork);
bool	is_dead(t_philo *philo, int extra_time);

#endif