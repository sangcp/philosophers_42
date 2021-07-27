/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:03:33 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/27 15:03:34 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork_mutex);
	if (chk_dead(philo))
	{
		pthread_mutex_unlock(philo->lfork_mutex);
		return (1);
	}
	philo_write(philo, "has taken fork");
	pthread_mutex_lock(philo->rfork_mutex);
	if (chk_dead(philo))
	{
		pthread_mutex_unlock(philo->lfork_mutex);
		pthread_mutex_unlock(philo->rfork_mutex);
		return (1);
	}
	philo_write(philo, "has taken fork");
	return (0);
}

void	philo_eat(t_philo *philo, int *eat)
{
	pthread_mutex_lock(&philo->last_ate_mutex);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->last_ate_mutex);
	philo_write(philo, "is eating");
	*eat += 1;
}

void	*start_thread(void *arg)
{
	t_philo	*philo;
	int		eat;

	philo = arg;
	eat = 0;
	if (philo->id % 2 == 1)
		usleep(200);
	while (eat != philo->data->eat_times && chk_dead(philo) == 0)
	{
		philo_write(philo, "is thinking");
		if (get_fork(philo))
			break ;
		philo_eat(philo, &eat);
		time_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->lfork_mutex);
		pthread_mutex_unlock(philo->rfork_mutex);
		if (chk_dead(philo))
			break ;
		philo_write(philo, "is sleeping");
		time_sleep(philo->data->time_to_sleep);
	}
	set_state(philo);
	return (NULL);
}

int	set_thread(t_data *data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		if (init_philo(data, &philo[i], i))
			return (1);
		if (pthread_create(&thread[i], NULL, start_thread, &philo[i]))
			return (1);
		++i;
	}
	dead_chk(philo, data);
	i = 0;
	while (i < data->num)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	return (0);
}
