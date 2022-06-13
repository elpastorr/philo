/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:42 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/13 19:25:24 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nbr)
{
	int		nb;
	int		neg;
	size_t	i;

	i = 0;
	nb = 0;
	neg = 1;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			neg = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
		nb = (nb * 10 + (nbr[i++] - '0'));
	return (nb * neg);
}

long int	get_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print(char *msg, t_philo *philo, int id)
{
	long int	time;

	pthread_mutex_lock(&(philo->arg->print));
	time = get_time();
	if (!check_death(philo))
		printf("%ld : philo %d %s\n", time - philo->arg->time, id, msg);
	pthread_mutex_lock(&(philo->arg->print));
}

void	ft_usleep(t_philo *philo, long int wait, long int time)
{
    while (time + wait > get_time() && check_death(philo))
        usleep(10);
}

void	sleepy_time(t_philo *philo)
{
	long int	time;

	time = get_time();
	print("is sleeping", philo, philo->id);
	ft_usleep(philo, philo->arg->t_sleep, get_time());
}

void	timetofeast(t_philo *philo)
{
	long int	time;

	time = get_time();
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = time;
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	print("is eating", philo, philo->id);
	ft_usleep(philo, philo->arg->t_eat, get_time());
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->arg->lock_start));
	pthread_mutex_unlock(&(philo->arg->lock_start));
	while (!check_full(philo) && !check_death(philo)/* && (philo->arg->max_eat < 0 || philo->n_eat < philo->arg->max_eat)*/)
	{
		// take_forks() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		pthread_mutex_lock(&(philo->fork));
		print("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->next_fork);
		print("has taken a fork", philo, philo->id);
		if (!check_death(philo))
		{
			timetofeast(philo);
			philo->n_eat += 1;
			if (philo->n_eat == philo->arg->max_eat)
			{
				pthread_mutex_lock(&(philo->full.mutex));
				philo->full.data = 1;
				pthread_mutex_unlock(&(philo->full.mutex));
			}
			sleepy_time(philo);
		}
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(philo->next_fork);
		
	}
	return (NULL);
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

void	launch_philos(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->arg->n_philo)
		pthread_create(&(env->philos[i].thread), NULL, routine, &(env->philos[i]));
}

void	create_philos(t_env *env)
{
	int i;

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
			env->philos[i].next_fork = &env->philos[(i + 1) % env->arg->n_philo].fork;
	}
	launch_philos(env);
}

void	check_arg(t_env *env, int ac)
{
	if (env->arg->n_philo < 1)
		ft_error(env, "ERROR : Nombre de philos non valide\n");
	if (env->arg->t_die < 60)
		ft_error(env, "ERROR : Time to die non valide\n");
	if (env->arg->t_eat < 60)
		ft_error(env, "ERROR : Time to eat non valide\n");
	if (env->arg->t_sleep < 60)
		ft_error(env, "ERROR : Time to sleep non valide\n");
	if (ac == 6 && env->arg->max_eat < 0)
		ft_error(env, "ERROR : Max eat for philos non valide\n");
}

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
	pthread_mutex_init(&(env->arg->lock_start), NULL);
	env->philos = malloc(sizeof(t_philo) * env->arg->n_philo);
	return (env);
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

void	shut_philos(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->arg->n_philo)
		pthread_join(env->philos[i].thread, NULL);
	ft_error(env, "\n");
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
			if (time - env->philos[i].last_eat.data > env->arg->t_die || check_all_full(env))
			{
				pthread_mutex_unlock(&(env->philos[i].last_eat.mutex));
				if (!check_all_full(env))
					print("died", &env->philos[i], env->philos[i].id);
				pthread_mutex_lock(&(env->arg->dead.mutex));
				env->arg->dead.data = 1;
				pthread_mutex_unlock(&(env->arg->dead.mutex));
				shut_philos(env);
			}
			pthread_mutex_unlock(&(env->philos[i].last_eat.mutex));
			i++;
			usleep(10);
		}
	}
}

int main(int ac, char **av)
{
	t_env	*env;

	if (ac < 5 || ac > 6)
	{
		printf("ENTER : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	env = NULL;
	env = init_env(env, ac, av);
	if (!env)
		return (1);
	pthread_mutex_lock(&(env->arg->lock_start));
	create_philos(env);
	pthread_mutex_unlock(&(env->arg->lock_start));
	main_thread(env);
}