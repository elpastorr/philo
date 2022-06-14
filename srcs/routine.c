/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:55:17 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/14 19:13:44 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->arg->print));
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = get_time();
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	pthread_mutex_unlock(&(philo->arg->print));
	while (!check_full(philo) && !check_death(philo))
	{
		if (philo->next_fork)
		{
			lets_eat(philo);
			if (philo->n_eat == philo->arg->max_eat)
			{
				pthread_mutex_lock(&(philo->full.mutex));
				philo->full.data = 1;
				pthread_mutex_unlock(&(philo->full.mutex));
			}
			sleepy_time(philo);
		}
	}
	return (NULL);
}

void	print(char *msg, t_philo *philo, int id)
{
	long int	time;

	pthread_mutex_lock(&(philo->arg->print));
	time = get_time();
	if (!check_death(philo))
		printf("%ld : philo %d %s\n", time - philo->arg->time, id, msg);
	pthread_mutex_unlock(&(philo->arg->print));
}

void	lets_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(philo->fork));
		print("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->next_fork);
		print("has taken a fork", philo, philo->id);
		timetofeast(philo);
		philo->n_eat += 1;
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(philo->next_fork);
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		print("has taken a fork", philo, philo->id);
		pthread_mutex_lock(&(philo->fork));
		print("has taken a fork", philo, philo->id);
		timetofeast(philo);
		philo->n_eat += 1;
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_unlock(&(philo->fork));
	}
}

void	sleepy_time(t_philo *philo)
{
	long int	time;

	time = get_time();
	print("is sleeping", philo, philo->id);
	ft_usleep(philo, philo->arg->t_sleep, get_time());
	print("is thinking", philo, philo->id);
}

void	timetofeast(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = get_time();
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	print("is eating", philo, philo->id);
	ft_usleep(philo, philo->arg->t_eat, get_time());
}
