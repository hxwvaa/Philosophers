/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_slumber_ponder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:41:38 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 18:41:39 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolo.h"

int	ponderation(t_philo *philo)
{
	if (print_status(philo->sh_data, philo->id, THINK) == 1)
		return (1);
	return (0);
}

int	slumberment(t_philo *philo)
{
	if (print_status(philo->sh_data, philo->id, SLEEP) == 1)
		return (1);
	if (my_usleep(philo->sh_data->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}

int	consumption(t_philo *philo)
{
	int	first;
	int	second;

	law_and_order(philo, &first, &second);
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
	pardon_the_forks(philo, first, second);
	return (0);
}
