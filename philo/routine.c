/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:23:52 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:23:53 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_func(void *item)
{
	t_philo	*philo;

	philo = (t_philo *)item;
	if (philo->philo_id % 2 == 0)
		usleep(10000);
	while (!(philo->info->is_dead))
	{
		eating(philo);
		if (philo->info->eat_enough)
			break ;
		printing_status(philo->info, philo->philo_id - 1, "is sleeping");
		sleep_control(philo->info->sleep_time, philo->info);
		printing_status(philo->info, philo->philo_id - 1, "is thinking");
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork));
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	if (philo->info->philo_count == 1)
	{
		sleep_control(philo->info->die_time * 2, philo->info);
		pthread_mutex_unlock(&(philo->l_fork));
	}
	pthread_mutex_lock(philo->r_fork);
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	pthread_mutex_lock(&(philo->info->eating_mutex));
	printing_status(philo->info, philo->philo_id - 1, "is eating");
	philo->last_eat_time = current_timestamp();
	pthread_mutex_unlock(&(philo->info->eating_mutex));
	sleep_control(philo->info->eat_time, philo->info);
	philo->eat_count++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&(philo->l_fork));
}

void	is_died(t_data *data, t_philo *p)
{
	int	i;

	while (!(data->eat_enough))
	{
		i = -1;
		while (++i < data->philo_count && !(data->is_dead))
		{
			pthread_mutex_lock(&(data->eating_mutex));
			if (current_timestamp() - p[i].last_eat_time > (long)data->die_time)
			{
				printing_status(data, i, "died");
				data->is_dead = 1;
			}
			pthread_mutex_unlock(&(data->eating_mutex));
			usleep(100);
		}
		if (data->is_dead)
			break ;
		i = 0;
		while (data->must_eat != -1 && p[i].eat_count >= data->must_eat - 1
			&& i < data->philo_count)
			i++;
		if (i == data->philo_count)
			data->eat_enough = 1;
	}
}
