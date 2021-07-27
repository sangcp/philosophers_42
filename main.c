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

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*thread;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("argument error\n", 1, 0));
	if (parsing(&data, ac, av))
		return (ft_putstr_fd("parsing error\n", 1, 0));
	philo = malloc(sizeof(t_philo) * data.num);
	if (!philo)
		return (ft_putstr_fd("cant malloc\n", 1, 0));
	thread = malloc(sizeof(pthread_t) * data.num);
	if (!thread)
		return (ft_putstr_fd("cant malloc\n", 1, 0));
	if (set_thread(&data, philo, thread))
		return (ft_putstr_fd("thread error\n", 1, 0));
	free(philo);
	free(thread);
	free(data.forks);
	return (0);
}
