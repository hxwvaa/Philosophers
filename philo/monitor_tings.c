/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_tings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:26 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 18:41:27 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolo.h"

int	check_eats(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->philos[i].eat_count < data->num_eat)
			return (0);
		i++;
	}
	return (1);
}

void	consumption_concluded(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death = true;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->eat_mutex);
}

void	time_has_come(t_data *data, unsigned long long i)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death = true;
	pthread_mutex_unlock(&data->death_mutex);
	print_status(data, data->philos[i].id, DEAD);
	pthread_mutex_unlock(&data->eat_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data				*data;
	unsigned long long	i;

	data = (t_data *)arg;
	while (!deadlolo(data))
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (data->num_eat > 0 && check_eats(data))
			{
				consumption_concluded(data);
				return (NULL);
			}
			if (get_time() - data->philos[i].last_eat > data->time_to_die)
			{
				time_has_come(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat_mutex);
			i++;
		}
	}
	return (NULL);
}
