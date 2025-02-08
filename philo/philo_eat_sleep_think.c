/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_sleep_think.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:38 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 19:19:53 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	if (print_status(philo->sh_data, philo->id, THINK) == 1)
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_status(philo->sh_data, philo->id, SLEEP) == 1)
		return (1);
	if (my_usleep(philo->sh_data->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	int	first;
	int	second;

	fork_lock_order(philo, &first, &second);
	if (print_status(philo->sh_data, philo->id, FORK) == 1)
		return (1);
	if (print_status(philo->sh_data, philo->id, FORK) == 1)
		return (1);
	if (print_status(philo->sh_data, philo->id, EAT) == 1)
		return (1);
	if (my_usleep(philo->sh_data->time_to_eat, philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->sh_data->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->sh_data->eat_mutex);
	philo->sh_data->forks[philo->left_fork] = philo->id;
	philo->sh_data->forks[philo->right_fork] = philo->id;
	release_forks(philo, first, second);
	return (0);
}
