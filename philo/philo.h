/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:37:58 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/08 19:19:53 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_philo	t_philo;

typedef struct s_data
{
	unsigned long long	num_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	num_eat;
	int					*forks;
	t_philo				*philos;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_t			monitor;
	bool				death;
	ssize_t				start_time;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	unsigned long long	eat_count;
	unsigned long long	last_eat;
	pthread_t			thread;
	t_data				*sh_data;
}						t_philo;

// - UTILS FUNCTIONS - //
unsigned long long		ft_atoull(const char *str);
bool					scan_args(int argc, char **argv);
unsigned long long		get_time(void);
int						my_usleep(unsigned long long time, t_philo *philo);
int						print_status(t_data *data, int id, int status);

// - INITIALIZATION FUNCTIONS - //
int						init_data(t_data *data, int argc, char **argv);
int						init_philos(t_data *data);
int						init_mutex(t_data *data);
void					init_forks(t_data *data);

// - FREE AND DESTROY FUNCTIONS - //
void					free_data(t_data *data, int i);
void					destroy_mutex(t_data *data);

// - MONITOR FUNCTIONS - //
void					*monitor_routine(void *arg);
void					philo_died(t_data *data, unsigned long long i);
void					meals_concluded(t_data *data);
int						check_eats(t_data *data);

// - PHILO ROUTINE FUNCTIONS - //
int						create_philos_monitor(t_data *data);
void					*philo_routine(void *arg);
void					single_philo(t_philo *philo);
int						is_dead(t_data *sh_data);
int						philo_eat(t_philo *philo);
int						philo_sleep(t_philo *philo);
int						philo_think(t_philo *philo);

// - FORK FUNCTIONS - //
void					fork_lock_order(t_philo *philo, int *first, int *second);
void					lock_forks(t_philo *philo, int first, int second);
void					release_forks(t_philo *philo, int first, int second);
int						fork_checker(t_philo *philo, int first, int second);

#endif
