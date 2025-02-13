/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:37:58 by hbasheer          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:57 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLO_H
# define PHILOLO_H

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
	long long			num_eat;
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
long long				ft_atoll(const char *str);
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
void					time_has_come(t_data *data, unsigned long long i);
void					consumption_concluded(t_data *data);
int						check_eats(t_data *data);

// - LIFE CYCLE FUNCTIONS - //
int						create_philos_monitor(t_data *data);
void					*peristaltic_continuum(void *arg);
void					solitary_confinement(t_philo *philo);
int						deadlolo(t_data *sh_data);

// - CONSUME, SLUMBER, PONDER FUNCTIONS - //
int						consumption(t_philo *philo);
int						slumberment(t_philo *philo);
int						ponderation(t_philo *philo);

// - FORK FUNCTIONS - //
void					law_and_order(t_philo *philo, int *first, int *second);
void					arrest_the_forks(t_philo *philo, int first, int second);
void					pardon_the_forks(t_philo *philo, int first, int second);
int						fork_checkers(t_philo *philo, int first, int second);

#endif
