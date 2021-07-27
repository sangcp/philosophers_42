/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:55:48 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/27 14:55:49 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_data *data, t_philo *philo, int i)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = i + 1;
	philo->data = data;
	philo->lfork_mutex = &data->forks[i];
	philo->rfork_mutex = &data->forks[(i + 1) % data->num];
	philo->last_ate = get_time();
	if (pthread_mutex_init(&philo->last_ate_mutex, NULL))
		return (1);
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->phi_write, NULL))
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL))
		return (1);
	return (0);
}

int	parsing(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->state = ALIVE;
	data->eat_times = -1;
	if (ac == 6)
		data->eat_times = ft_atoi(av[5]);
	if (data->num <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 \
	|| data->time_to_sleep <= 0 || (ac == 6 && data->eat_times < 0))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num);
	if (!data->forks)
		return (1);
	if (mutex_init(data))
	{
		free(data->forks);
		ft_putstr_fd("mutex error\n", 1, 0);
	}
	data->starttime = get_time();
	return (0);
}
