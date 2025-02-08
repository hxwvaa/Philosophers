#include "philolo.h"

void destroy_mutex(t_data *data)
{
    unsigned long long i;

    i = 0;
    while (i < data->num_philo)
    {
        pthread_mutex_destroy(&data->fork_mutex[i]);
        i++;
    }
    pthread_mutex_destroy(&data->eat_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
}

void free_data(t_data *data, int i)
{
    free(data->forks);
    free(data->philos);
    if (i)
    {
        free(data->fork_mutex);
        destroy_mutex(data);
    }
}