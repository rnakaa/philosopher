#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "philosophers.h"

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
