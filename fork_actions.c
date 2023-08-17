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

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

