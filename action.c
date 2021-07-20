#include "philo.h"

void	print_status(t_phil *p, char *str, char *color)
{
	long	time;

	time = gettime(p->all->time);
	pthread_mutex_lock(&p->all->print);
	printf("%s%lu %d %s\n", color, time, p->id + 1, str);
	if (!p->dead)
		pthread_mutex_unlock(&p->all->print);
}

int	check_die(t_all *a, int i)
{
	long	time;

	time = gettime(a->time);
	if (a->phils[i].last_eat + a->time_to_die < time)
	{
		a->phils[i].dead = 1;
		print_status(&a->phils[i], "died", "\x1b[31m");
		free_all(a);
		return (0);
	}
	return (1);
}

void	*check_p(void *all)
{
	t_all	*a;
	int		i;
	int		count;

	a = (t_all *)all;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < a->number)
		{
			if (!check_die(a, i))
				return (NULL);
			count += a->phils[i].get_count;
			i++;
		}
		if (count == a->number)
		{
			free_all(a);
			return (NULL);
		}
	}
	return (NULL);
}

void	eat(t_phil *p)
{
	print_status(p, "is eating", "\x1b[32m");
	p->last_eat = gettime(p->all->time);
	p->eat_count++;
	if (p->eat_count == p->all->must_eat)
		p->get_count = 1;
	ft_usleep(p->all->time_to_eat);
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
}

void	*action(void *phil)
{
	t_phil	*p;

	p = (t_phil *)phil;
	while (1)
	{
		pthread_mutex_lock(p->left);
		print_status(p, "has taken left fork", "\x1b[34m");
		pthread_mutex_lock(p->right);
		print_status(p, "has taken right fork", "\x1b[34m");
		eat(p);
		print_status(p, "is sleeping", "\x1b[36m");
		ft_usleep(p->all->time_to_sleep);
		print_status(p, "is thinking", "\x1b[35m");
	}
	return (NULL);
}
