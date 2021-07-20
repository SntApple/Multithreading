#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_all	t_all;

typedef struct s_phil
{
	int				id;
	int				dead;
	int				eat_count;
	int				get_count;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	t_all			*all;
	long			last_eat;
}				t_phil;

typedef struct s_all
{
	int				number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			time;
	pthread_mutex_t	*forks;
	t_phil			*phils;
	pthread_mutex_t	print;
}				t_all;

int		check_args(int argc, char **argv, t_all *all);
int		init(t_all *all);
void	*action(void *phil);
void	*check_p(void *all);
void	free_all(t_all *all);
void	ft_usleep(int in);
long	gettime(long start);
#endif