/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:00:47 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/27 15:00:48 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

void	set_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state == ALIVE)
		philo->data->state = DONE;
	pthread_mutex_unlock(&philo->data->state_mutex);
}

int	chk_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	if ((get_time() - philo->last_ate) >= \
	(unsigned long)philo->data->time_to_die)
		philo->data->state = DEAD;
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state == DEAD)
		ret = 1;
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (ret);
}

void	time_sleep(unsigned long time_to_sleep)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time_to_sleep)
		usleep(100);
}

int	dead_chk(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philo[i].last_ate_mutex);
		if (get_time() - philo[i].last_ate >= (unsigned long)data->time_to_die)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (data->state != DONE)
				data->state = DEAD;
			if (data->state == DEAD)
				philo_write(&philo[i], "dead");
			pthread_mutex_unlock(&data->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].last_ate_mutex);
		i++;
		if (i >= data->num)
			i = 0;
	}
	return (0);
}
