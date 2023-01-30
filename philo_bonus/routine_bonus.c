/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:25:38 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:25:39 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*process_func(t_philo	*philo)
{
	philo->last_eat_time = current_timestamp();
	pthread_create(&philo->info->thread, NULL, &is_died, philo);
	if (philo->philo_id % 2 == 0)
		usleep(10000);
	while (!(philo->info->is_dead))
	{
		eating(philo);
		if (philo->eat_count >= philo->info->must_eat
			&& philo->info->must_eat != -1)
			break ;
		printing_status(philo->info, philo->philo_id - 1, "is sleeping");
		sleep_control(philo->info->sleep_time, philo->info);
		printing_status(philo->info, philo->philo_id - 1, "is thinking");
	}
	pthread_join(philo->info->thread, NULL);
	if (philo->info->is_dead)
		exit(1);
	exit(0);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->info->forks);
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	sem_wait(philo->info->forks);
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	sem_wait(philo->info->eating_sem);
	printing_status(philo->info, philo->philo_id - 1, "is eating");
	philo->last_eat_time = current_timestamp();
	sem_post(philo->info->eating_sem);
	sleep_control(philo->info->eat_time, philo->info);
	philo->eat_count++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	*is_died(void *item)
{
	t_philo	*p;
	t_data	*data;

	p = (t_philo *)item;
	data = p->info;
	while (1)
	{
		sem_wait(data->eating_sem);
		if (current_timestamp() - p->last_eat_time > (long)data->die_time)
		{
			printing_status(data, p->philo_id - 1, "died");
			data->is_dead = 1;
			exit(1);
		}
		sem_post(data->eating_sem);
		if (data->is_dead)
			break ;
		if (p->eat_count >= data->must_eat && data->must_eat != -1)
			break ;
		usleep(1000);
	}
	return (0);
}
