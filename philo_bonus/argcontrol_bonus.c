/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcontrol_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:25:03 by tcelik            #+#    #+#             */
/*   Updated: 2023/01/30 10:25:04 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	argument_control(char **av)
{
	if (check_num(av))
		return (0);
	return (1);
}
