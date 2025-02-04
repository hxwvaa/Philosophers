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

unsigned long long get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
