/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:12:58 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/01 17:24:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdint.h>

typedef struct s_data
{
	uint32_t		start_time;
	uint32_t		philo_count;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		max_meals;
	uint32_t		max_meals_reached;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	finished_mut;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	uint32_t		last_meal;
	uint32_t		total_meals;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

void		cleanup(t_data *data, t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep_and_think(t_philo *philo);
void		print_status(t_philo *philo, const char *status);
int			ft_atoi(const char *str);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_philo *philo, t_data *data);
int			start_simulation(t_philo *philo);
uint32_t	get_time(void);
int			ft_error(const char *str, t_data *data, t_philo *philo);

#endif