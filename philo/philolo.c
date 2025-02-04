#include "philolo.h"

int my_usleep(long time, t_philo *philo)
{
    unsigned long long start;

    start = get_time();
    while (get_time() < start + time)
    {
        if(deadlolo(philo->sh_data))
            return 1;
        usleep(100);
    }
    return(0);
}


int print_status(t_data *data, int id, int status)
{
    // ssize_t time;
    pthread_mutex_lock(&data->print_mutex);
    if (!deadlolo(data))
    {
        // time = get_time();
        // if (time == -1)
        //     return(-1);
        printf("%lld %d ", get_time() - data->start_time, id);
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
    return (0);
}

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

int deadlolo(t_data *sh_data)
{
    unsigned long long i;

    i = 0;
    pthread_mutex_lock(&sh_data->death_mutex);
    if (sh_data->death == false)
        i = 0;
    else
        i = 1;
    pthread_mutex_unlock(&sh_data->death_mutex);
    return (i);
}

void law_and_order(t_philo *philo, int *first, int *second)
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

int fork_checkers(t_philo *philo, int first, int second)
{
    int first_id;
    int second_id;

    pthread_mutex_lock(&philo->sh_data->fork_mutex[first]);
    first_id = philo->sh_data->forks[first];
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
    pthread_mutex_lock(&philo->sh_data->fork_mutex[second]);
    second_id = philo->sh_data->forks[second];
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
    if (first_id != philo->id && second_id != philo->id)
    {
        pthread_mutex_lock(&philo->sh_data->fork_mutex[first]);
        pthread_mutex_lock(&philo->sh_data->fork_mutex[second]);
        return(1);
    }
    return(0);
}

int peristaltic_continuum(t_philo *philo)
{
    int first;
    int second;

    if (!deadlolo(philo->sh_data))
    {
        print_status(philo->sh_data, philo->id, FORK);
        print_status(philo->sh_data, philo->id, FORK);
        print_status(philo->sh_data, philo->id, EAT);
        if (my_usleep(philo->sh_data->time_to_eat, philo) == 1)
            return(1);
        pthread_mutex_lock(&philo->sh_data->eat_mutex);
        philo->last_eat = get_time();
        philo->eat_count++;
        pthread_mutex_unlock(&philo->sh_data->eat_mutex);
        philo->sh_data->forks[philo->left_fork] = philo->id;
        philo->sh_data->forks[philo->right_fork] = philo->id;
        law_and_order(philo, &first, &second);
        pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
        pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
        print_status(philo->sh_data, philo->id, SLEEP);
        if (my_usleep(philo->sh_data->time_to_sleep, philo) == 1)
            return(1);
        print_status(philo->sh_data, philo->id, THINK);
    }
    return(0);
}


void *philo_routine(void *arg)
{
    t_philo *philo;

    int first;
    int second;
    
    philo = (t_philo *)arg;
    // printf("\nnum_philo: %llu\n", philo->sh_data->num_philo);
    if (philo->sh_data->num_philo == 1)
    {
        my_usleep(philo->sh_data->time_to_die, philo);
        print_status(philo->sh_data, philo->id, DEAD);
        return(NULL);
    }
    while (!deadlolo(philo->sh_data))
    {
        law_and_order(philo, &first, &second);
        if (fork_checkers(philo, first, second))
        {
            if (peristaltic_continuum(philo) == 1)
                return(NULL);
        }
    }
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
    return (NULL);
}

void *monitor_routine(void *arg)
{
    t_data *data;
    unsigned long long i;

    data = (t_data *)arg;
    while (!deadlolo(data))
    {
        i = 0;
        while (i < data->num_philo)
        {
            pthread_mutex_lock(&data->eat_mutex);
            if (data->num_eat > 0 && data->philos[i].eat_count >= data->num_eat)
            {
                pthread_mutex_lock(&data->death_mutex);
                data->death = true;
                pthread_mutex_unlock(&data->death_mutex);
                pthread_mutex_unlock(&data->eat_mutex);
                return (NULL);
            }
            if (get_time() - data->philos[i].last_eat > data->time_to_die)
            {
                pthread_mutex_lock(&data->death_mutex);
                data->death = true;
                pthread_mutex_unlock(&data->death_mutex);
                print_status(data, i, DEAD);
                pthread_mutex_unlock(&data->eat_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->eat_mutex);
            i++;
        }
        usleep(100);
    }
    return (NULL);
}

int create_philos(t_data *data)
{
    unsigned long long i;

    i = 0;
    while (i < data->num_philo)
    {
        if (pthread_create(&data->philos[i].thread,
                NULL, &philo_routine, &data->philos[i]))
            return (printf("Error: pthread_create failed\n"), 1);
        i++;
    }
    if (pthread_create(&data->monitor, NULL, &monitor_routine, data))
        return (printf("Error: pthread_create failed\n"), 1);
    if (pthread_join(data->monitor, NULL))
        return (printf("Error: pthread_join failed\n"), 1);
    while (i < data->num_philo)
    {
        if (pthread_join(data->philos[i].thread, NULL))
            return (printf("Error: pthread_join failed\n"), 1);
        i++;
    }
    return(0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (printf("Error: Wrong number of arguments\n"), 1);
    if (!scan_args(argc, argv))
        return (printf("Error: Invalid arguments\n"), 1);
    if (init_data(&data, argc, argv))
        return(1);
    if (data.num_eat == 0)
        return (0);
    if (init_philos(&data))
        return(free(data.forks), free(data.philos) , 1);
    if(init_mutex(&data))
        return(free(data.forks), free(data.philos) , 1);
    if(create_philos(&data))
        return(free(data.forks), free(data.philos) , 1);
    // if (start_simulation(&data))
    //     return (1);
    destroy_mutex(&data);
    return (0);
}
