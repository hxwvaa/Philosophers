#include "philolo.h"

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
        return(1);
    return(0);
}

void pardon_the_forks(t_philo *philo, int first, int second)
{
    law_and_order(philo, &first, &second);
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[first]);
    pthread_mutex_unlock(&philo->sh_data->fork_mutex[second]);
}

void arrest_the_forks(t_philo *philo, int first, int second)
{
    law_and_order(philo, &first, &second);
    pthread_mutex_lock(&philo->sh_data->fork_mutex[first]);
    pthread_mutex_lock(&philo->sh_data->fork_mutex[second]);
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
