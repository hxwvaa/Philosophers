/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:31 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 19:39:41 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_checker(t_philo *philo, int first, int second)
{
	int	first_id;
	int	second_id;

	pthread_mutex_lock(&philo->sh_data->fork_mutex[first]);
	first_id = philo->sh_data->forks[first];
	pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
	pthread_mutex_lock(&philo->sh_data->fork_mutex[second]);
	second_id = philo->sh_data->forks[second];
	pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
	if (first_id != philo->id && second_id != philo->id)
		return (1);
	return (0);
}

void	release_forks(t_philo *philo, int first, int second)
{
	lock_order(philo, &first, &second);
	pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
	pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
}

void	lock_forks(t_philo *philo, int first, int second)
{
	lock_order(philo, &first, &second);
	pthread_mutex_lock(&philo->sh_data->fork_mutex[first]);
	pthread_mutex_lock(&philo->sh_data->fork_mutex[second]);
}

void	lock_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}
