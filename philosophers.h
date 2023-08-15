#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	int	num;
	time_t	last_eat;
	int	eat_time;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int	num;
	time_t	die_time;
	time_t	eat_time;
	time_t	sleep_time;
	time_t	start_time;
	int	eat_num;
	bool	counter;
	t_philo philo[200];
	pthread_mutex_t m_philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	print;
}	t_data;

#endif
