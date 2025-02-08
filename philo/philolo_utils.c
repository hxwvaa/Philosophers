#include "philolo.h"

unsigned long long	ft_atoull(const char *str)
{
	unsigned long long	nb;
	int					i;

	nb = 0;
	i = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (str[i])
		i++;
	if (i > 19)
		return (ULONG_MAX);
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb);
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
            return (true);
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (true);
            j++;
        }
        i++;
    }
    return (false);
}

unsigned long long get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int my_usleep(unsigned long long time, t_philo *philo)
{
    unsigned long long start;

    start = get_time();
    while (get_time() - start < time)
    {
        if(deadlolo(philo->sh_data))
            return 1;
        usleep(500);
    }
    return(0);
}

int print_status(t_data *data, int id, int status)
{
    pthread_mutex_lock(&data->print_mutex);
    if (status == DEAD)
        printf("%llu %d died\n", get_time() - data->start_time, id);
    if (deadlolo(data))
        return(pthread_mutex_unlock(&data->print_mutex), 1);
    if (!deadlolo(data))
    {
        printf("%llu %d ", get_time() - data->start_time, id);
        if (status == EAT)
            printf("is eating\n");
        else if (status == SLEEP)
            printf("is sleeping\n");
        else if (status == THINK)
            printf("is thinking\n");
        else if (status == FORK)
            printf("has taken a fork\n");
    }
    pthread_mutex_unlock(&data->print_mutex);
    return (0);
}
