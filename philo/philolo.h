#ifndef PHILOLO_H
#define PHILOLO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

#define EAT 0
#define SLEEP 1
#define THINK 2
#define FORK 3
#define DEAD 4

typedef struct s_philo
{
    int id;
    int left_fork;
    int right_fork;
    int eat_count;
    long last_eat;
    pthread_t thread;
} t_philo;

typedef struct s_data
{
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_must_eat;
    int *forks;
    t_philo *philos;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    bool death;
} t_data;


unsigned long long ft_atoull(const char *str);


#endif