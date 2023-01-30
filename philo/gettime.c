/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:23:09 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:23:13 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
