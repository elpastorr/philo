/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:50:38 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/21 17:58:31 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arg(t_env *env, int ac)
{
	if (env->arg->n_philo < 1 || env->arg->n_philo > 200)
		ft_error(env, "ERROR : Nombre de philos non valide\n");
	if (env->arg->t_die < 60)
		ft_error(env, "ERROR : Time to die non valide\n");
	if (env->arg->t_eat < 60)
		ft_error(env, "ERROR : Time to eat non valide\n");
	if (env->arg->t_sleep < 60)
		ft_error(env, "ERROR : Time to sleep non valide\n");
	if (ac == 6 && env->arg->max_eat <= 0)
		ft_error(env, "ERROR : Max eat for philos non valide\n");
}

int	check_death(t_philo *philo)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(&(philo->arg->dead.mutex));
	if (philo->arg->dead.data == 1)
		tmp = 1;
	pthread_mutex_unlock(&(philo->arg->dead.mutex));
	return (tmp);
}

int	check_full(t_philo *philo)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(&(philo->full.mutex));
	if (philo->full.data == 1)
		tmp = 1;
	pthread_mutex_unlock(&(philo->full.mutex));
	return (tmp);
}

int	check_all_full(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->arg->n_philo)
		if (!check_full(&env->philos[i]))
			return (0);
	return (1);
}
