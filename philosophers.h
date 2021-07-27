/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangcpar <sangcpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 09:14:52 by sangcpar          #+#    #+#             */
/*   Updated: 2021/07/25 09:14:53 by sangcpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define DEAD 0
# define ALIVE 1
# define DONE 2

typedef struct s_data
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				state;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	phi_write;
	unsigned long	starttime;
}					t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_ate;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*rfork_mutex;
	pthread_mutex_t	last_ate_mutex;
	t_data			*data;
}					t_philo;

// utils.c
void			ft_putchar_fd(char c, int fd);
void			ft_put_ul_fd(unsigned long n, int fd);
int				ft_putstr_fd(const char *s, int fd, int ret);
int				ft_atoi(const char *str);
void			philo_write(t_philo *philo, char *s);
// parsing.c
int				init_philo(t_data *data, t_philo *philo, int i);
int				parsing(t_data *data, int ac, char **av);
// thread_utils.c
unsigned long	get_time(void);
int				chk_dead(t_philo *philo);
void			time_sleep(unsigned long time_to_sleep);
int				dead_chk(t_philo *philo, t_data *data);
void			set_state(t_philo *philo);
// start_thread.c
int				set_thread(t_data *data, t_philo *philo, pthread_t *thread);

#endif
