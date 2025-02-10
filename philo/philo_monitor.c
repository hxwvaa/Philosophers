/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:26 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/10 11:24:22 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eats(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->philos[i].eat_count < (unsigned long long)data->num_eat)
			return (0);
		i++;
	}
	return (1);
}

void	meals_concluded(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death = true;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->eat_mutex);
}

void	philo_died(t_data *data, unsigned long long i)
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
	while (!is_dead(data))
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (data->num_eat > 0 && check_eats(data))
			{
				meals_concluded(data);
				return (NULL);
			}
			if ((__int128_t) get_time() - (__int128_t)data->philos[i].last_eat > data->time_to_die)
			{
				philo_died(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat_mutex);
			i++;
		}
	}
	return (NULL);
}
