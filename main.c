#include <pthread.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREAD 4
#define ADD_NUM 100000

#include <stdlib.h>
#include <pthread.h>

// 構造体の定義
// 初期化関数
// スレッド作成関数
// 哲学者のライフサイクル関数

int main(int argc, char **argv) {
    if (argc < 5) {
        // 引数が不足している場合のエラーハンドリング
        return 1;
    }

    int number_of_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);

    t_philosopher *philosophers = malloc(number_of_philosophers * sizeof(t_philosopher));
    t_fork *forks = malloc(number_of_philosophers * sizeof(t_fork));

    initialize_philosophers_and_forks(philosophers, forks, number_of_philosophers);

    for (int i = 0; i < number_of_philosophers; i++) {
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;
    }

    create_philosopher_threads(philosophers, number_of_philosophers);

    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }

    free(philosophers);
    free(forks);

    return 0;
}

