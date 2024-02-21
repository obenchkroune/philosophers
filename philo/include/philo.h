/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:44:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/21 00:18:03 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

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
	long			start;
	uint32_t		count;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		time_to_die;
	uint32_t		max_meals;
	bool			philo_died;
	pthread_mutex_t	mut;
	pthread_mutex_t	meals_mut;
	uint32_t		max_meals_reached;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	uint32_t		idx;
	uint32_t		right;
	uint32_t		left;
	pthread_t		tid;
	pthread_mutex_t	meal_mut;
	t_data			*data;
	long			last_meal;
	bool			is_eating;
	uint32_t		total_meals;
}	t_philo;

void	ft_usleep(t_philo *philo, uint32_t time);
void	eat(t_philo *philo);
bool	is_dead(t_philo *philo);
bool	is_over(t_data *data);
bool	check_errors(int ac, char **av);
size_t	ft_strlen(const char *str);
void	ft_putstrfd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_atoi(const char *n);
void	init_philo(t_philo **philo, int ac, char **av);
void	cleanup_philo(t_philo *philo);
void	run_philo(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
long	ft_timestamp(void);
void	print_state(t_philo *philo, t_state state);

#endif