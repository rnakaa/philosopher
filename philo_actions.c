/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:02:09 by rnaka             #+#    #+#             */
/*   Updated: 2023/08/19 01:34:50 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	update_eat_time(t_data *data, t_philo *philo)
{
	int	i;

	i = philo->num;
	if (data->counter)
	{
		pthread_mutex_lock(&data->m_philo[i]);
		philo->eat_time++;
		pthread_mutex_unlock(&data->m_philo[i]);
	}
	return (false);
}

int	philoeat(t_data *data, t_philo *philo)
{
	time_t	start;
	int		i;

	if (take_fork(data, philo) || printmessage(data, philo, "is eating"))
	{
		drop_fork(philo);
		return (true);
	}
	start = now_time();
	i = philo->num;
	pthread_mutex_lock(&data->m_philo[i]);
	philo->last_eat = start;
	pthread_mutex_unlock(&data->m_philo[i]);
	while (now_time() - start < data->eat_time)
		usleep(100);
	drop_fork(philo);
	return (update_eat_time(data, philo));
}

// int	philoeat(t_data *data, t_philo *philo)
// {
// 	time_t	start;
// 	int		i;
// 	time_t	now;

// 	now = now_time();
// 	i = philo->num;
// 	if (take_fork(data, philo))
// 		return (true);
// 	if (printmessage(data, philo, "is eating"))
// 	{
// 		drop_fork(philo);
// 		return (true);
// 	}
// 	start = now_time();
// 	pthread_mutex_lock(&data->m_philo[i]);
// 	philo->last_eat = start;
// 	pthread_mutex_unlock(&data->m_philo[i]);
// 	while (now_time() - start < data->eat_time)
// 		usleep(100);
// 	if (data->counter)
// 	{
// 		pthread_mutex_lock(&data->m_philo[i]);
// 		philo->eat_time++;
// 		pthread_mutex_unlock(&data->m_philo[i]);
// 	}
// 	drop_fork(philo);
// 	return (false);
// }

int	philosleep(t_data *data, t_philo *philo)
{
	time_t	start;

	if (printmessage(data, philo, "is sleeping"))
		return (true);
	start = now_time();
	while (now_time() - start < data->sleep_time)
		usleep(100);
	return (false);
}

int	philothink(t_data *data, t_philo *philo)
{
	if (printmessage(data, philo, "is thinking"))
		return (true);
	return (false);
}

void	*philo_job(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->num % 2)
		usleep(100);
	while (true)
	{
		if (philoeat(data, philo))
			return (NULL);
		if (philosleep(data, philo))
			return (NULL);
		if (philothink(data, philo))
			return (NULL);
	}
}
