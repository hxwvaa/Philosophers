/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:38:11 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 18:38:12 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (scan_args(argc, argv))
		return (printf("Error: Invalid arguments\n"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	if (data.num_eat == 0)
		return (0);
	if (init_philos(&data))
		return (free_data(&data, 0), 1);
	if (init_mutex(&data))
		return (free_data(&data, 0), 1);
	if (create_philos_monitor(&data))
		return (free_data(&data, 1), 1);
	free_data(&data, 1);
	return (0);
}
