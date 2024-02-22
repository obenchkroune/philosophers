/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:46:32 by obenchkr          #+#    #+#             */
/*   Updated: 2024/02/22 20:23:42 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	data->philo_died = false;
	sem_unlink("/death");
	sem_unlink("/forks");
	data->death_sem = sem_open("/death", O_CREAT | O_EXCL, 0644, 1);
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->count);
	data->max_meals_reached = 0;
	data->start = ft_timestamp();
	return (data);
}

static void	init_individual_philo(t_philo *philo, uint32_t i)
{
	char	*nbr;
	char	*eating_sem_name;
	char	*meal_sem_name;

	nbr = ft_itoa(i);
	eating_sem_name = ft_strjoin("/eating", nbr);
	meal_sem_name = ft_strjoin("/meal", nbr);
	free(nbr);
	sem_unlink(eating_sem_name);
	sem_unlink(meal_sem_name);
	philo[i].eating_sem = sem_open(
		eating_sem_name, O_CREAT | O_EXCL, 0664, 1);
	philo[i].meal_sem = sem_open(
		meal_sem_name, O_CREAT | O_EXCL, 0664, 1);
	philo[i].eating_sem_name = eating_sem_name;
	philo[i].meal_sem_name = meal_sem_name;
	philo[i].total_meals = 0;
	philo[i].idx = i;
	philo[i].last_meal = ft_timestamp();
	philo[i].is_eating = false;
}

void	init_philo(t_philo **philo_ptr, int ac, char **av)
{
	t_data		*data;
	uint32_t	i;
	t_philo		*philo;

	data = init_data(ac, av);
	philo = malloc(sizeof(t_philo) * data->count);
	if (!philo)
		return ;
	i = 0;
	while (i < data->count)
	{
		init_individual_philo(&philo[i], i);
		philo[i].data = data;
		i++;
	}
	*philo_ptr = philo;
}
