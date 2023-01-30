/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:25:48 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:25:49 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	spc_chrc(char c)
{
	if ((c == ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		neg;

	neg = 1;
	i = 0;
	num = 0;
	while (spc_chrc(str[i]) == 1)
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + str[i++] - 48;
		if (num * neg < -2147483648)
			return (0);
		if (num * neg > 2147483647)
			return (-1);
	}
	return (neg * num);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

void	printing_status(t_data *data, int philo_num, char *state)
{
	sem_wait(data->printing_sem);
	if (ft_strncmp("died", state, 4) == 0 && data->is_dead == 0)
	{
		data->is_dead = 1;
		printf("%lli ", current_timestamp() - data->start_time);
		printf("%i ", philo_num + 1);
		printf("%s\n", state);
		return ;
	}
	if (!(data->is_dead))
	{
		printf("%lli ", current_timestamp() - data->start_time);
		printf("%i ", philo_num + 1);
		printf("%s\n", state);
	}
	sem_post(data->printing_sem);
	return ;
}
