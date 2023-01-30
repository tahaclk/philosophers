/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:24:25 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:24:26 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					philo_id;
	int					eat_count;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	long long			last_eat_time;
	struct s_data		*info;
	pthread_t			thread;
}	t_philo;

typedef struct s_data
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				eat_enough;
	int				philo_count;
	long long		start_time;
	int				is_dead;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	printing_mutex;
	t_philo			*philos;
}	t_data;

int			check_num(char **str);
void		*thread_func(void *item);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			init_data(t_data *data, char **av, int ac);
int			init_philos(t_data *data);
void		eating(t_philo *philo);
void		destroy(t_data *data);
int			process_init(t_data *item);
void		is_died(t_data *data, t_philo *p);
void		sleep_control(long long time, t_data *data);
long long	current_timestamp(void);
int			argument_control(char **av);
void		printing_status(t_data *data, int philo_num, char *state);

#endif
