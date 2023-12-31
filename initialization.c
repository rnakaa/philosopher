/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:01:54 by rnaka             #+#    #+#             */
/*   Updated: 2023/08/19 01:59:10 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	reset(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
		pthread_mutex_init(&data->fork[i++], NULL);
	i = 0;
	data->stop = false;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->finish, NULL);
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

void	philo_thread(t_data *data)
{
	int			i;
	pthread_t	thread_monitor;

	i = 0;
	data->start_time = now_time();
	while (i < data->num)
	{
		data->philo[i].data = data;
		pthread_create(&data->philo[i].thread,
			NULL, philo_job, &data->philo[i]);
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

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_mutex_destroy(&data->m_philo[i]);
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->finish);
}
