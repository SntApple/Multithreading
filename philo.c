#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (1);
	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv, all))
		{
			if (!init(all))
				return (1);
		}
		else
		{
			printf("Invalid arguments");
			return (0);
		}
	}
	else
	{
		printf("Invalid arguments");
		return (0);
	}
}
