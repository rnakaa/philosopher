#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "philosophers.h"

void	set_fork(t_data *data, t_philo *philo, int i)
{
	if (i % 2)
	{
		philo->right_fork = &data->fork[i];
		if (i == data->num - 1)
			philo->left_fork = &data->fork[0]; 
		else
			philo->left_fork = &data->fork[i + 1];
	}
	else
	{
		philo->left_fork = &data->fork[i];
		if (i == data->num - 1)
			philo->right_fork = &data->fork[0];
		else
			philo->right_fork = &data->fork[i + 1];
	}
}

void	reset(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num)
		pthread_mutex_init(&data->fork[i++], NULL);
	i = 0;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->num)
	{
		data->philo[i].num = i;
		pthread_mutex_init(&data->m_philo[i], NULL);
		data->philo[i].eat_time = 0;
		set_fork(data, &data->philo[i], i);
		i++;
	}
}

time_t	now_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec*1000 + time.tv_usec/1000);
}

void	printmessage(t_data *data, t_philo *philo, char *str)
{
	time_t	now;

	now = now_time();
	pthread_mutex_lock(&data->print);
	printf("%ld %d %s\n", (int)data->start_time - now, philo->num + 1, str);
	pthread_mutex_unlock(&data->print);
}

void	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printmessage(data, philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	printmessage(data, philo, "has taken a fork");
}

void	drop_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philoeat(t_data *data, t_philo *philo)
{
	time_t	start;
	int	i;
	int	wait_time;

	i = philo->num;
	take_fork(data, philo);
	printmessage(data, philo, "is eating");
	start = now_time();
	pthread_mutex_lock(&data->m_philo[i]);
	philo->last_eat = start;
	pthread_mutex_unlock(&data->m_philo[i]);
	wait_time = data->eat_time - (now_time() - start);
	if (wait_time > 0)
		usleep(wait_time * 1000);
	if (data->counter)
	{
		pthread_mutex_lock(&data->m_philo[i]);
		philo->eat_time++;
		pthread_mutex_unlock(&data->m_philo[i]);
	}
	drop_fork(data, philo);
}

void	philosleep(t_data *data, t_philo *philo)
{
	int	wait_time;

	printmessage(data, philo, "is sleeping");
	wait_time = data->sleep_time;
	if (wait_time > 0)
		usleep(wait_time * 1000);
}

void	philothink(t_data *data, t_philo *philo)
{
	printmessage(data, philo, "is thinking");
	usleep(100);
}

void	*philo_job(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (true)
	{
		philoeat(data, philo);
		philosleep(data, philo);
		philothink(data, philo);
	}
}

void	philo_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = now_time();
	while (i < data->num)
	{
		data->philo[i].data = data;
		pthread_create(&data->philo[i].thread, NULL, philo_job, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	data.num = atoi(argv[1]);
	data.die_time = atoi(argv[2]);
	data.eat_time = atoi(argv[3]);
	data.sleep_time = atoi(argv[4]);
	if(argc == 5)
	{
		data.counter = true;
		data.eat_num = atoi(argv[5]);
	}
	reset(&data);
	philo_thread(&data);
}
