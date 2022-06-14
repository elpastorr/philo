/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:00:55 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/14 19:12:41 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env	*init_env(t_env *env, int ac, char **av)
{
	env = malloc(sizeof(t_env));
	env->arg = malloc(sizeof(t_arg));
	env->arg->n_philo = ft_atoi(av[1]);
	env->arg->t_die = ft_atoi(av[2]);
	env->arg->t_eat = ft_atoi(av[3]);
	env->arg->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->arg->max_eat = ft_atoi(av[5]);
	else
		env->arg->max_eat = -1;
	check_arg(env, ac);
	env->arg->time = get_time();
	pthread_mutex_init(&(env->arg->print), NULL);
	pthread_mutex_init(&(env->arg->dead.mutex), NULL);
	env->arg->dead.data = 0;
	pthread_mutex_init(&(env->arg->print), NULL);
	env->philos = malloc(sizeof(t_philo) * env->arg->n_philo);
	return (env);
}

void	main_thread(t_env *env)
{
	int			i;
	long int	time;

	while (1)
	{
		i = 0;
		while (i < env->arg->n_philo && env->philos[i].thread)
		{
			time = get_time();
			pthread_mutex_lock(&(env->philos[i].last_eat.mutex));
			if (((time - env->philos[i].last_eat.data) > env->arg->t_die
					&& !check_full(&env->philos[i])) || check_all_full(env))
			{
				dead_thread(env, i);
			}
			pthread_mutex_unlock(&(env->philos[i].last_eat.mutex));
			i++;
		}
	}
}

void	dead_thread(t_env *env, int i)
{
	pthread_mutex_unlock(&env->philos[i].last_eat.mutex);
	if (!check_all_full(env))
		print("died", &env->philos[i], env->philos[i].id);
	pthread_mutex_lock(&(env->arg->dead.mutex));
	env->arg->dead.data = 1;
	pthread_mutex_unlock(&(env->arg->dead.mutex));
	shut_philos(env);
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac < 5 || ac > 6)
	{
		printf("ENTER : ./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	env = NULL;
	env = init_env(env, ac, av);
	if (!env)
		return (1);
	create_philos(env);
	main_thread(env);
	free(env->arg);
	free(env->philos);
	free(env);
}
