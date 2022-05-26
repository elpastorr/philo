/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:42 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/26 18:22:32 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine()

void    ft_error(t_env *env, char *s)
{
    printf("%s", s);
    free(env);
    exit(1);
}

long int    get_time(void)
{
    struct timeval  time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    create_philos(t_env *env)
{
    int i;

    i = 0;
    while (i < env->n_philo)
    {
        env->philos->
    }
}

void    check_arg(t_env *env, int ac)
{
    if (env->n_philo < 0)
        ft_error(env, "ERROR : Nombre de philos non valide\n");
    if (env->t_die < 0)
        ft_error(env, "ERROR : Time to die non valide\n");
    if (env->t_eat < 0)
        ft_error(env, "ERROR : Time to eat non valide\n");
    if (env->t_sleep < 0)
        ft_error(env, "ERROR : Time to sleep non valide\n");
    if (ac == 6 && env->max_eat < 1)
        ft_error(env, "ERROR : Max eat for philos non valide\n");
}

void    init_env(t_env *env, int ac, char **av)
{
    env->n_philo = ft_atoi(av[1]);
    env->t_die = ft_atoi(av[2]);
    env->t_eat = ft_atoi(av[3]);
    env->t_sleep = ft_atoi(av[4]);
    if (ac == 6)
        env->max_eat = ft_atoi(av[5]);
    else
        env->max_eat = -1;
    check_arg(env, ac);
    env->time = get_time();
    env->philos = malloc(sizeof(t_philo) * env->n_philo);
}

int main(int ac, char **av)
{
    t_env   env;

    if (ac < 5 || ac > 6)
    {
        printf("ENTER : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    env = malloc(sizeof(t_env));
    if (!env)
        return (1);
    init_env(env, ac, av);
    create_philos(env);
}