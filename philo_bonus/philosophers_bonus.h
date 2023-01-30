/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:24:40 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:24:41 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	long long		last_eat_time;
	int				pid_no;
	struct s_data	*info;
}	t_philo;

typedef struct s_data
{
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			must_eat;
	int			eat_enough;
	int			philo_count;
	long long	start_time;
	int			is_dead;
	sem_t		*eating_sem;
	sem_t		*forks;
	sem_t		*printing_sem;
	t_philo		*philos;
	pthread_t	thread;
}	t_data;

int			check_num(char **str);
void		*process_func(t_philo *philo);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			init_data(t_data *data, char **av, int ac);
int			init_philos(t_data *data);
void		eating(t_philo *philo);
void		destroy_sem(t_data *data);
int			process_init(t_data *item);
void		*is_died(void *item);
void		sleep_control(long long time, t_data *data);
long long	current_timestamp(void);
int			argument_control(char **av);
void		printing_status(t_data *data, int philo_num, char *state);

#endif
