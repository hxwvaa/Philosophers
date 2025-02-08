/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:33 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 19:01:59 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolo.h"

void	destroy_mutex(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

void	free_data(t_data *data, int i)
{
	free(data->forks);
	free(data->philos);
	if (i == 1)
	{
		destroy_mutex(data);
		free(data->fork_mutex);
	}
}
