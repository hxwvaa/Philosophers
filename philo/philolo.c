#include "philolo.h"

void my_usleep(long time)
{
    long start;

    start = get_time();
    while (get_time() < start + time)
        usleep(100);
}

ssize_t get_time(void)
{
    struct timeval time;

    if(gettimeofday(&time, NULL) == -1)
    {
        printf("Error: gettimeofday failed\n");
        exit(-1);
    }
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int print_status(t_data *data, int id, int status)
{
    ssize_t time;
    pthread_mutex_lock(&data->print_mutex);
    if (data->death == false)
    {
        time = get_time();
        if (time == -1)
            return(-1);
        printf("%ld %d ",  - data->philos[0].last_eat, id + 1);
        if (status == EAT)
            printf("is eating\n");
        else if (status == SLEEP)
            printf("is sleeping\n");
        else if (status == THINK)
            printf("is thinking\n");
        else if (status == FORK)
            printf("has taken a fork\n");
        else if (status == DEAD)
            printf("died\n");
    }
    pthread_mutex_unlock(&data->print_mutex);
}

void init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philo)
    {
        data->philos[i].id = i;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->num_philo;
        data->philos[i].eat_count = 0;
        data->philos[i].last_eat = get_time();
        i++;
    }
}

int init_mutex(t_data *data)
{
    int i;

    i = 0;
    data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    if (!data->fork_mutex)
    {
        printf("Error: Malloc failed\n");
        return(1);
    }
    while (i < data->num_philo)
    {
        pthread_mutex_init(&data->fork_mutex[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->death_mutex, NULL);
    return(0);
}

void destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philo)
    {
        pthread_mutex_destroy(&data->fork_mutex[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
}

int init_data(t_data *data, int argc, char **argv)
{
    data->num_philo = ft_atoull(argv[1]);
    data->time_to_eat = ft_atoull(argv[3]);
    data->time_to_die = ft_atoull(argv[2]);
    data->time_to_sleep = ft_atoull(argv[4]);
    data->num_must_eat = -1;
    if (argc == 6)
        data->num_must_eat = ft_atoull(argv[5]);
    data->forks = malloc(sizeof(int) * data->num_philo); // need to init the forks id
    data->philos = malloc(sizeof(t_philo) * data->num_philo);
    if (!data->forks || !data->philos)
    {
        printf("Error: Malloc failed\n");
        return (1);
    }
    return (0);
}

bool scan_args(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        if (!argv[i][j])
            return (false);
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    if (!scan_args(argc, argv))
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    if (init_data(&data, argc, argv))
        return (1);
    init_philos(&data);
    if(init_mutex(&data))
    {
        free(data.forks);
        free(data.philos);
        return (1);
    }
    // if (start_simulation(&data))
    //     return (1);
    destroy_mutex(&data);
    return (0);
}