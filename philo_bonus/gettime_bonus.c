/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:25:15 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:25:16 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long long	current_timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te. tv_sec * 1000 + te. tv_usec / 1000);
}

void	sleep_control(long long time, t_data *data)
{
	long long	i;

	i = current_timestamp();
	while (!(data->is_dead))
	{
		if ((current_timestamp() - i) >= time)
			break ;
		usleep(50);
	}
}
