#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "philosophers.h"
int	is_arg_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if ('0' > argv[i] || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	char	c;

	if (!str)
	    return 0;
	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && c - '0' > INT_MAX % 10))
			return 0;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}


int	check_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (is_arg_num(argv[1]) || is_arg_num(argv[2]) || is_arg_num(argv[3]) || is_arg_num(argv[4]))
		return (1);
	if (argc == 6 && is_arg_num(argv[5]))
		return (1);
	if (!ft_atoi(argv[2]) || !ft_atoi(argv[3]) || !ft_atoi(argv[4]) || !ft_atoi(argv[1]) || ft_atoi(argv[1]) > 200)
		return (1);
	if (argc == 6 && !ft_atoi(argv[5]))
		return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arguments(argc, argv))
		return (1);
	data.num = ft_atoi(argv[1]);
	data.die_time = ft_atoi(argv[2]);
	data.eat_time = ft_atoi(argv[3]);
	data.sleep_time = ft_atoi(argv[4]);
	data.counter = false;
	if(argc == 6)
	{
		data.counter = true;
		data.eat_num = ft_atoi(argv[5]);
	}
	reset(&data);
	philo_thread(&data);
	return (1);
}
