/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolo_inits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:23 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:32 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philo = ft_atoll(argv[1]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_sleep = ft_atoll(argv[4]);
	data->num_eat = -1;
	if (argc == 6)
		data->num_eat = ft_atoll(argv[5]);
	if (data->num_philo >= INT_MAX || data->time_to_eat >= INT_MAX
		|| data->time_to_die >= INT_MAX || data->time_to_sleep >= INT_MAX
		|| (argc == 6 && data->num_eat >= INT_MAX))
		return (printf("Error: Invalid arguments\n"), 1);
	if (argc == 6 && data->num_eat == 0)
		return (0);
	data->forks = malloc(sizeof(int) * data->num_philo);
	if (!data->forks)
		return (printf("Error: Malloc failed\n"), 1);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (free(data->forks), printf("Error: Malloc failed\n"), 1);
	init_forks(data);
	data->death = false;
	return (0);
}

int	init_philos(t_data *data)
{
	unsigned long long	i;

	i = 0;
	data->start_time = get_time();
	if (data->start_time == -1)
		return (1);
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philo;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start_time;
		data->philos[i].sh_data = data;
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	unsigned long long	i;

	i = 0;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->fork_mutex)
	{
		printf("Error: Malloc failed\n");
		return (1);
	}
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (0);
}

void	init_forks(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (i == 0 || i == data->num_philo - 1)
			data->forks[i] = data->num_philo;
		else if (i % 2 == 0)
			data->forks[i] = i + 2;
		else
			data->forks[i] = i + 1;
		i++;
	}
}
