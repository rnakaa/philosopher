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

time_t	now_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec*1000 + time.tv_usec/1000);
}
void	reset(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num)
		pthread_mutex_init(&data->fork[i++], NULL);
	i = 0;
	data->stop = false;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->num)
	{
		data->philo[i].num = i;
		pthread_mutex_init(&data->m_philo[i], NULL);
		data->philo[i].eat_time = 0;
		set_fork(data, &data->philo[i], i);
		data->philo[i].last_eat = now_time();
		i++;
	}
}


int	printmessage(t_data *data, t_philo *philo, char *str)
{
	time_t	now;

	now = now_time();
	pthread_mutex_lock(&data->finish);
	pthread_mutex_lock(&data->print);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->finish);
		return (true);
	}
	pthread_mutex_unlock(&data->finish);
	printf("%ld %d %s\n", now - data->start_time, philo->num + 1, str);
	pthread_mutex_unlock(&data->print);
	return (false);
}

int	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (printmessage(data, philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (true);
	}
	pthread_mutex_lock(philo->left_fork);
	if (printmessage(data, philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	return (false);
}

void	drop_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	philoeat(t_data *data, t_philo *philo)
{
	time_t	start;
	int	i;
	int	wait_time;

	i = philo->num;
	if (take_fork(data, philo))
		return (true);
	if (printmessage(data, philo, "is eating"))
	{
		drop_fork(data, philo);
		return (true);
	}
	start = now_time();
	pthread_mutex_lock(&data->m_philo[i]);
	philo->last_eat = start;
	pthread_mutex_unlock(&data->m_philo[i]);
	while (now_time() - start < data->eat_time)
		usleep(100);
	if (data->counter)
	{
		pthread_mutex_lock(&data->m_philo[i]);
		philo->eat_time++;
		pthread_mutex_unlock(&data->m_philo[i]);
	}
	drop_fork(data, philo);
	return (false);
}

int	philosleep(t_data *data, t_philo *philo)
{
	time_t	start;

	start = now_time();
	if (printmessage(data, philo, "is sleeping"))
		return (true);
	while (now_time() - start < data->sleep_time)
		usleep(100);
	return (false);
}

int	philothink(t_data *data, t_philo *philo)
{
	if (printmessage(data, philo, "is thinking"))
		return (true);
	usleep(100);
	return (false);
}

void	*philo_job(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->num % 2)
		usleep(100);
	while (true)
	{
		if (philoeat(data, philo))
			return NULL;
		if (philosleep(data, philo))
			return NULL;
		if (philothink(data, philo))
			return NULL;
	}
}

int	check(t_data *data)
{
	int		i;
	time_t	now;

	i = 0;
	while (i < data->num)
	{
		pthread_mutex_lock(&data->m_philo[i]);
		now = now_time();
		if (now - data->philo[i].last_eat > data->die_time)
		{
			pthread_mutex_lock(&data->finish);
			pthread_mutex_lock(&data->print);
			printf("%ld %d %s\n", now - data->start_time, i + 1, "is dead");
			data->stop = true;
			pthread_mutex_unlock(&data->print);
			pthread_mutex_unlock(&data->finish);
			pthread_mutex_unlock(&data->m_philo[i]);
			return (true);
		}
		pthread_mutex_unlock(&data->m_philo[i]);
		i++;
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_data *data = (t_data *)arg;

	while (true)
	{
		if (check(data))
			return NULL;
	}
}

void	philo_thread(t_data *data)
{
	int	i;
	pthread_t	thread_monitor;

	i = 0;
	data->start_time = now_time();
	while (i < data->num)
	{
		data->philo[i].data = data;
		pthread_create(&data->philo[i].thread, NULL, philo_job, &data->philo[i]);
		i++;
	}
	pthread_create(&thread_monitor, NULL, monitor, data);
	i = 0;
	while (i < data->num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(thread_monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	data.num = atoi(argv[1]);
	data.die_time = atoi(argv[2]);
	data.eat_time = atoi(argv[3]);
	data.sleep_time = atoi(argv[4]);
	data.counter = false;
	if(argc == 6)
	{
		data.counter = true;
		data.eat_num = atoi(argv[5]);
		printf("%d\n", atoi(argv[5]));
	}
	reset(&data);
	philo_thread(&data);
}
