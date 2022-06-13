#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_env {
    int             id;
    pthread_t       thread;
    pthread_mutex_t write;
}	t_env;

long int	get_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    *routine(void *void_env)
{
    t_env   *env;
    env = (t_env *)void_env;
    pthread_mutex_lock(&env->write);
    printf("Thread %d is executing at %ld\n", env->id, (get_time()/1000));
    pthread_mutex_unlock(&env->write);
}

void	ft_usleep(long int wait, long int time)
{
    while (time + wait > get_time())
        usleep(10);
}


int	main(int ac, char **av)
{
    long int    time = get_time();
    printf("%ld, time = %ld\n", get_time() - time, get_time());
    ft_usleep(5, get_time());
    printf("%ld, time = %ld\n", get_time() - time, get_time());
    ft_usleep(10, get_time());
    printf("%ld\n", get_time() - time);

    printf("%ld\n", get_time() - time);
    ft_usleep(5, get_time());
    printf("%ld\n", get_time() - time);
    ft_usleep(10, get_time());
    printf("%ld\n", get_time() - time);
    // int i;
    // t_env   *env;

    // env = malloc(sizeof(t_env));
    // env->id = 0;
    // pthread_mutex_init(&env->write, NULL);
    // i = 0;
    // while (i < 4)
    // {
    //     if (pthread_create(&(env[i].thread), NULL, routine, env))
    //     {
    //         printf("Thread creation error\n");
    //         exit(1);
    //     }
    //     printf("Thread %d has started at %ld\n", i, get_time());
    //     // pthread_mutex_lock(&env->write);
    //     i++;
    //     env->id++;
    //     // pthread_mutex_unlock(&env->write);
    // }
    // i = 0;
    // // pthread_mutex_lock(&env->write);
    // env->id = 0;
    // // pthread_mutex_unlock(&env->write);
    // while (i < 4)
    // {
    //     if (pthread_join(env[i].thread, NULL))
    //     {
    //         printf("Thread join error\n");
    //         exit(2);
    //     }
    //     printf("Thread %d has finished at %ld\n", i, get_time());
    //     i++;
    //     env->id++;
    // }

}