/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:03:12 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/27 14:03:14 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

void	ft_put_ul_fd(unsigned long n, int fd)
{
	if (n >= 10)
	{
		ft_put_ul_fd(n / 10, fd);
		ft_put_ul_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

int	ft_putstr_fd(const char *s, int fd, int ret)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
	return (ret);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	result;

	result = 0;
	sign = 1;
	while (*str == ' ')
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

void	philo_write(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->phi_write);
	ft_put_ul_fd(get_time() - philo->data->starttime, 1);
	ft_putstr_fd("ms\t", 1, 0);
	ft_put_ul_fd(philo->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(s, 1, 0);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(&philo->data->phi_write);
}
