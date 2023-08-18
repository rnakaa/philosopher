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
	bool	stop;
	t_philo philo[200];
	pthread_mutex_t	finish;
	pthread_mutex_t	m_philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	print;
}	t_data;

void	set_fork(t_data *data, t_philo *philo, int i);
time_t	now_time();
void	reset(t_data *data);
int	printmessage(t_data *data, t_philo *philo, char *str);
int	take_fork(t_data *data, t_philo *philo);
void	drop_fork(t_philo *philo);
int	philoeat(t_data *data, t_philo *philo);
int	philosleep(t_data *data, t_philo *philo);
int	philothink(t_data *data, t_philo *philo);
void	*philo_job(void *arg);
int	check(t_data *data);
bool	num_eat(t_data *data);
void	*monitor(void *arg);
void	philo_thread(t_data *data);

#endif
