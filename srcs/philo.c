/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:42 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/24 18:23:37 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_env(t_env *env, int ac, char **av)
{
    env->philo = ft_atoi(av[1]);
    env->t_die = ft_atoi(av[2]);
    env->t_eat = ft_atoi(av[3]);
    env->t_sleep = ft_atoi(av[4]);
    if (ac == 6)
        env->max_eat = ft_atoi(av[5]);
    else
        env->max_eat = -1;
}

int main(int ac, char **av)
{
    t_env   env;

    if (ac < 5 || ac > 6)
    {
        printf("ENTER : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return(0);
    }
    
}