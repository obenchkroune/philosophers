/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:03 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/12 15:00:33 by obenchkr         ###   ########.fr       */
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
typedef enum status t_status;

enum status {
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	HAS_FORK
};

struct s_data
{
	int				philo_count;
	int				max_meals;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	bool			finished;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print_lock;
};

struct s_philo
{
	pthread_t	thread_id;
	t_data		*data;
	int			idx;
	long		last_meal;
};

int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
bool	check_errors(int ac, char **av);
int		ft_strcmp(const char *str1, const char *str2);
t_data	*init_data(int ac, char **av);
t_philo	**init_philo(t_data *data);
long	ft_timestamp(void);
void	run_philosophers(t_data *data, t_philo **philo);


#endif