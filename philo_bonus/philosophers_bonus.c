/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:25:26 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:25:27 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_data(t_data *data, char **av, int ac)
{
	data->philo_count = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->is_dead = 0;
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
	sem_unlink("/eating_semaphore");
	sem_unlink("/printing_semaphore");
	sem_unlink("/forks");
	data->eating_sem = sem_open("/eating_semaphore", O_CREAT, S_IRWXU, 1);
	data->printing_sem = sem_open("/printing_semaphore", O_CREAT, S_IRWXU, 1);
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->philo_count);
	while (++i < data->philo_count)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].info = data;
		data->philos[i].philo_id = i + 1;
	}
	return (1);
}

void	destroy_sem(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->philo_count)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->philo_count)
				kill(data->philos[i].pid_no, 15);
			break ;
		}
		i++;
	}
	sem_unlink("/eating_semaphore");
	sem_unlink("/printing_semaphore");
	sem_unlink("/forks");
	sem_close(data->eating_sem);
	sem_close(data->printing_sem);
	sem_close(data->forks);
	free(data->philos);
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
		data->philos[i].pid_no = fork();
		if (data->philos[i].pid_no < 0)
			return (0);
		else if (data->philos[i].pid_no == 0)
			process_func(&data->philos[i]);
		usleep(100);
		i++;
	}
	destroy_sem(data);
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
