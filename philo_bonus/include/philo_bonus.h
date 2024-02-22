/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:15:58 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/22 20:17:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS

# define PHILO_BONUS

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

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
	long		start;
	uint32_t	count;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	time_to_die;
	uint32_t	max_meals;
	bool		philo_died;
	uint32_t	max_meals_reached;
	sem_t		*forks_sem;
	sem_t		*death_sem;
}	t_data;

typedef struct s_philo
{
	uint32_t	idx;
	pid_t		pid;
	t_data		*data;
	long		last_meal;
	bool		is_eating;
	uint32_t	total_meals;
	sem_t		*meal_sem;
	sem_t		*eating_sem;
	char		*meal_sem_name;
	char		*eating_sem_name;
}	t_philo;

char	*ft_itoa(int n);
long	ft_timestamp(void);
bool	check_errors(int ac, char **av);
size_t	ft_strlen(const char *str);
void	ft_putstrfd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_atoi(const char *n);
void	ft_usleep(t_philo *philo, uint32_t time);
char	*ft_strjoin(const char *s1, const char *s2);
void	init_philo(t_philo **philo, int ac, char **av);

#endif