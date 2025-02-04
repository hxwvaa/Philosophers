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

typedef struct s_philo t_philo;

typedef struct s_data
{
    unsigned long long num_philo;
    unsigned long long time_to_die;
    unsigned long long time_to_eat;
    unsigned long long time_to_sleep;
    unsigned long long num_eat;
    int *forks;
    t_philo *philos;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t eat_mutex;
    pthread_t monitor;
    bool death;
    ssize_t start_time;
} t_data;

typedef struct s_philo
{
    int id;
    int left_fork;
    int right_fork;
    unsigned long long eat_count;
    unsigned long long last_eat;
    pthread_t thread;
    t_data *sh_data;
} t_philo;



// - UTILS FUNCTIONS -
unsigned long long ft_atoull(const char *str);
bool scan_args(int argc, char **argv);
unsigned long long get_time(void);
int deadlolo(t_data *sh_data);
int my_usleep(long time, t_philo *philo);
int print_status(t_data *data, int id, int status);


// - INITIALIZATION FUNCTIONS -
int init_data(t_data *data, int argc, char **argv);
int init_philos(t_data *data);
int init_mutex(t_data *data);
void init_forks(t_data *data);

#endif
