#include"philosophers.h"

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

