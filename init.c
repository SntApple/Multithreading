#include "philo.h"

pthread_mutex_t	new_f(void)
{
	pthread_mutex_t	f;

	pthread_mutex_init(&f, NULL);
	return (f);
}

t_phil	new_p(t_all *all, int i)
{
	t_phil	p;

	p.id = i;
	p.dead = 0;
	p.last_eat = gettime(all->time);
	p.all = all;
	p.eat_count = 0;
	p.get_count = 0;
	return (p);
}

void	init_p(t_phil *phil)
{
	int			i;
	pthread_t	check;

	i = 0;
	pthread_create(&check, NULL, check_p, phil->all);
	while (i < phil->all->number)
	{
		pthread_create(&phil[i].thread, NULL, action, &phil[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	if (phil->all->number > 1)
	{
		while (i < phil->all->number)
		{
			pthread_create(&phil[i].thread, NULL, action, &phil[i]);
			i += 2;
		}
	}
	pthread_join(check, NULL);
}

void	give_forks(t_phil *phil, pthread_mutex_t *forks)
{
	if (phil->id == phil->all->number - 1)
	{
		phil->left = &forks[phil->id];
		phil->right = &forks[0];
	}
	else
	{
		phil->left = &forks[phil->id];
		phil->right = &forks[phil->id + 1];
	}
}

int	init(t_all *all)
{
	int	i;

	all->time = gettime(0);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->number);
	if (!all->forks)
		return (0);
	i = 0;
	while (i < all->number)
	{
		all->forks[i] = new_f();
		i++;
	}
	pthread_mutex_init(&all->print, NULL);
	i = 0;
	all->phils = malloc(sizeof(t_phil) * all->number);
	if (!all->phils)
		return (0);
	while (i < all->number)
	{
		all->phils[i] = new_p(all, i);
		give_forks(&all->phils[i], all->forks);
		i++;
	}
	init_p(all->phils);
	return (1);
}
