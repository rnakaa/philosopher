#include"philosophers.h"

time_t	now_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec*1000 + time.tv_usec/1000);
}
