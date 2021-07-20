#include "philo.h"

void	free_all(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->number)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	free(all->forks);
	free(all->phils);
	pthread_mutex_destroy(&all->print);
}

void	ft_usleep(int in)
{
	time_t	start;
	time_t	end;

	start = gettime(0);
	end = gettime(0) + in;
	while (start < end)
	{
		usleep(10);
		start = gettime(0);
	}
}

long	gettime(long start)
{
	long			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time - start);
}
