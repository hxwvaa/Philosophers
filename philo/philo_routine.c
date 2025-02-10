/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:28 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/10 11:16:46 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *sh_data)
{
	unsigned long long	i;

	i = 0;
	pthread_mutex_lock(&sh_data->death_mutex);
	if (sh_data->death == false)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&sh_data->death_mutex);
	return (i);
}

void	single_philo(t_philo *philo)
{
	my_usleep(philo->sh_data->time_to_die, philo);
	pthread_mutex_lock(&philo->sh_data->death_mutex);
	philo->sh_data->death = true;
	pthread_mutex_unlock(&philo->sh_data->death_mutex);
	print_status(philo->sh_data, philo->id, DEAD);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)arg;
	if (philo->sh_data->num_philo == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	while (!is_dead(philo->sh_data))
	{
		lock_order(philo, &first, &second);
		if (fork_checker(philo, first, second))
		{
			lock_forks(philo, first, second);
			if (philo_eat(philo) == 1)
				return (release_forks(philo, first, second), NULL);
			if (philo_sleep(philo) == 1)
				return (NULL);
			if (philo_think(philo) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

int	create_philos_monitor(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]))
			return (printf("Error: pthread_create failed\n"), 1);
		i++;
	}
	if (data->num_philo > 1 && pthread_create(&data->monitor, NULL,
			&monitor_routine, data))
		return (printf("Error: pthread_create failed\n"), 1);
	if (data->num_philo > 1 && pthread_join(data->monitor, NULL))
		return (printf("Error: pthread_join failed\n"), 1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Error: pthread_join failed\n"), 1);
		i++;
	}
	return (0);
}
