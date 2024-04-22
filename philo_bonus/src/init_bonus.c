/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:31:16 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 19:25:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_SYNC);
	sem_unlink(SEM_MEAL);
	data->stop_sem = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0644, 1);
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->philo_count);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	data->sync_sem = sem_open(SEM_SYNC, O_CREAT | O_EXCL, 0644, 1);
	data->meal_sem = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 1);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	return (data);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;
	uint32_t	i;

	data = init_data(ac, av);
	philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo)
	{
		free(data);
		exit(1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		philo[i].data = data;
		philo[i].total_meals = 0;
		philo[i].idx = i;
		philo[i].next_meal = ft_timestamp() + data->time_to_die;
		sem_unlink("/meal");
		philo[i].sem = sem_open("/meal", O_CREAT | O_EXCL, 0666, 1);
		i++;
	}
	return (philo);
}
