/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:31:16 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 23:51:51 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*safe_sem_init(const char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(1);
	}
	return (sem);
}

void	init_data(t_data *data, int ac, char **av)
{
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->forks = safe_sem_init(SEM_FORKS, data->philo_count);
	data->print_sem = safe_sem_init(SEM_PRINT, 1);
	data->sync_sem = safe_sem_init(SEM_SYNC, 1);
	data->meal_sem = safe_sem_init(SEM_MEAL, 1);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
}

void	init_philo(t_philo *philo, t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		philo[i].data = data;
		philo[i].total_meals = 0;
		philo[i].idx = i;
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		i++;
	}
}
