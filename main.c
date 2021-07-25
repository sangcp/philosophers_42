/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 09:14:32 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/25 09:14:35 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
void philo_write(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->pen);
	printf("%ld\t%d %s\n", get_time() - philo->data->starttime, philo->id, s);
	pthread_mutex_unlock(&philo->data->pen);
}
unsigned long get_time()
{
	struct timeval tv;
	unsigned long time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

int			chk_dead(t_philo *philo)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state == DEAD)
		ret = 1;
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (ret);
}

int			ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	result;

	result = 0;
	sign = 1;
	while (iswhitespace(*str))
		str++;
	if (*str == '-' || (*str < '0' && *str > '9'))
		return (-1);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (10 * result) + (*str - '0');
		str++;
	}
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	else if (result >= 9223372036854775807)
		return (-1);
	return (sign * result);
}

int mutex_init(t_data *data)
{
	int i;
	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->pen, NULL))
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL))
		return (1);
	return (0);
}

int parsing(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nb_phil = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_times = ft_atoi(av[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_phil);
	if (!data->forks)
		return (1);
	if (mutex_init(data))
	{
		free(data->forks);
		printf("mutex error\n");
	}
	data->starttime = get_time();
	return (0);
}

int init_philo(t_data *data, t_philo *philo, int i)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = i + 1;
	philo->data = data;
	philo->lfork_mutex = &data->forks[i];
	philo->rfork_mutex = &data->forks[(i + 1) % data->nb_phil];
	philo->last_ate = get_time();
	if (pthread_mutex_init(&philo->last_ate_mutex, NULL))
		return (1);
	return (0);
}

int get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork_mutex);
	if (chk_dead(philo))
	{
		pthread_mutex_unlock(&philo->lfork_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->rfork_mutex);
	if (chk_dead(philo))
	{
		pthread_mutex_unlock(&philo->lfork_mutex);
		pthread_mutex_unlock(&philo->rfork_mutex);
		return (1);
	}
	philo_write(philo, "has taken fork");
	return (0);
}

void start_thread(void *arg)
{
	t_philo *philo;
	int eat;

	philo = arg;
	eat = 0;
	if (philo->id % 2 == 1)
		usleep(200);
	while (eat < philo->data->eat_times && chk_dead(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->pen);
		printf("%ld\t%d is thinking\n", get_time() - philo->data->starttime, philo->id);
		pthread_mutex_unlock(&philo->data->pen);
		if (get_fork(philo))
			return ;
	}

}

int set_thread(t_data *data, t_philo *philo, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (init_philo(data, &philo[i], i))
			return (1);
		if (pthread_create(&thread[i], NULL, start_thread, &philo[i]))
			return (1);
		++i;
	}
}

int main(int ac, char **av)
{
	t_data data;
	t_philo *philo;
	pthread_t *thread;

	if (ac != 5 || ac != 6)
		printf("argument error\n");
	if (parsing(&data, ac, av))
		printf("parsing error\n");
	thread = malloc(sizeof(pthread_t) * data.nb_phil);
	if (!thread)
		return (1);
	if (set_thread(&data, philo, thread))
	{
		printf("thread error\n");
		return (1);
	}
}
