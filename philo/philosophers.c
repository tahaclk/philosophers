/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:23:40 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:23:41 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, char **av, int ac)
{
	data->philo_count = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->is_dead = 0;
	data->eat_enough = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	if (data->die_time < 0 || data->eat_time < 0)
		return (0);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat <= 0)
			return (0);
	}
	else
		data->must_eat = -1;
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->eating_mutex, NULL);
	pthread_mutex_init(&data->printing_mutex, NULL);
	while (++i < data->philo_count)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].info = data;
		data->philos[i].philo_id = i + 1;
		pthread_mutex_init(&(data->philos[i].l_fork), NULL);
		if (i == data->philo_count - 1)
			data->philos[i].r_fork = &(data->philos[0].l_fork);
		else
			data->philos[i].r_fork = &(data->philos[i + 1].l_fork);
	}
	return (1);
}

void	destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i].thread, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&(data->philos[i].l_fork));
	pthread_mutex_destroy(&(data->eating_mutex));
	pthread_mutex_destroy(&(data->printing_mutex));
}

int	process_init(t_data *item)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)item;
	data->start_time = current_timestamp();
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&thread_func, &(data->philos[i])))
			return (0);
		data->philos[i].last_eat_time = current_timestamp();
		i++;
	}
	is_died(data, data->philos);
	destroy(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!argument_control(av))
			printf("Wrong Argument!\n");
		if (!init_data(&data, av, ac))
			return (-1);
		if (!init_philos(&data))
			return (-1);
		if (!process_init(&data))
			return (-1);
	}
	else
		printf("Wrong Argument!\n");
}
