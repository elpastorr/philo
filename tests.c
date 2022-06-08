#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_env {
    int         id;
    pthread_t   thread;
}	t_env;

void    *routine(void *void_env)
{
    t_env   *env;
    env = (t_env *)void_env;
    printf("Thread %d is executing\n", env->id);
}

int	main(int ac, char **av)
{
    int i;
    t_env   *env;

    env = malloc(sizeof(t_env) * 4);
    env[0].id = 0;
    env[1].id = 1;
    env[2].id = 2;
    env[3].id = 3;
    i = 0;
    while (i < 4)
    {
        if (pthread_create(&(env[i].thread), NULL, routine, &(env[i])))
        {
            printf("Thread creation error\n");
            exit(1);
        }
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (pthread_join(env[i].thread, NULL))
        {
            printf("Thread join error\n");
            exit(2);
        }
        printf("Thread %d has finished\n", i);
        i++;
    }
}