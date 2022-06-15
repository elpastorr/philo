/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:52:13 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/15 16:07:18 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philos(t_env *env)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&(env->arg->print));
	while (++i < env->arg->n_philo)
		pthread_create(&(env->philos[i].thread),
			NULL, routine, &(env->philos[i]));
	pthread_mutex_unlock(&(env->arg->print));
}

void	create_philos(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->arg->n_philo)
	{
		pthread_mutex_init(&(env->philos[i].fork), NULL);
		pthread_mutex_init(&(env->philos[i].last_eat.mutex), NULL);
		env->philos[i].last_eat.data = get_time();
		pthread_mutex_init(&(env->philos[i].full.mutex), NULL);
		env->philos[i].full.data = 0;
		env->philos[i].arg = env->arg;
		env->philos[i].id = i + 1;
		env->philos[i].n_eat = 0;
	}
	i = -1;
	while (++i < env->arg->n_philo)
	{
		if (env->arg->n_philo == 1)
			env->philos[i].next_fork = NULL;
		else
			env->philos[i].next_fork = &(
					env->philos[(i + 1) % env->arg->n_philo].fork);
	}
	launch_philos(env);
}

void	ft_error(t_env *env, char *s)
{
	printf("%s", s);
	if (env)
	{
		if (env->arg)
			free(env->arg);
		if (env->philos)
			free(env->philos);
		free(env);
	}
	exit(1);
}

void	shut_philos(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->arg->n_philo)
		pthread_join(env->philos[i].thread, NULL);
	ft_error(env, "");
}
