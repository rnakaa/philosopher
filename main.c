#include <pthread.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *philo(void *arg)
{
	while (1)
		if (i == 3)
			break ;
	printf("haihaihai\n");
}

void *gen_philo(void *arg)
{
   int	i;
   pthread_t philo[3];
   
   i = 0;
   while (i < 3)
   {
	if (pthread_create(&philo[i], NULL, philo, NULL) != 0)
		printf("error\n");
   	i++;
   }
   sleep(1);
}

int main(void)
{
   pthread_t thread;
   void *retval;

   if (pthread_create(&thread, NULL, gen_philo, NULL) != 0)
       // エラー処理
       return (0);
   // 1. スレッドが終了するまで待つ
   pthread_join(thread, &retval);
   // 2. スレッドを待たない
   // pthread_detach(thread);
   return (0);
}

