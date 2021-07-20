#include "philo.h"

int	get_num(char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num *= 10;
			num += str[i] - '0';
		}
		else
			return (0);
		i++;
	}
	return (num);
}

int	check_args(int argc, char **argv, t_all *all)
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		num = get_num(argv[i]);
		if (num == 0)
			return (0);
		if (argc == 5)
			all->must_eat = -1;
		if (i == 1)
			all->number = num;
		else if (i == 2)
			all->time_to_die = num;
		else if (i == 3)
			all->time_to_eat = num;
		else if (i == 4)
			all->time_to_sleep = num;
		else if (i == 5)
			all->must_eat = num;
		i++;
	}
	return (1);
}
