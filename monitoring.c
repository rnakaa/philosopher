#include"philosophers.h"

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

bool	num_eat(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num)
	{
		pthread_mutex_lock(&data->m_philo[i]);
		if (data->eat_num > data->philo[i].eat_time)
		{
			pthread_mutex_unlock(&data->m_philo[i]);
			return (false);
		}
		pthread_mutex_unlock(&data->m_philo[i]);
		i++;
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_data *data = (t_data *)arg;

	while (true)
	{
		if (check(data))
			return NULL;
		if (data->counter && num_eat(data))
		{
			pthread_mutex_lock(&data->finish);
			data->stop = true;
			pthread_mutex_unlock(&data->finish);
			break ;
		}
	}
	return NULL;
}
