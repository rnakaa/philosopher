/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:02:05 by rnaka             #+#    #+#             */
/*   Updated: 2023/08/18 23:16:54 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
