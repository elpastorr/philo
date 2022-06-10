/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:49:42 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/10 19:17:24 by elpastor         ###   ########.fr       */
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

void	print(char *msg, t_philo *philo, int id)
{
	int			tmp;
	long int	time;

	tmp = 0;
	while (!tmp && !check_death(philo))
	{
		pthread_mutex_lock(&(philo->print.mutex));
		tmp = philo->print.data;
		if (tmp)
			philo->print.data = 0;
		pthread_mutex_unlock(&(philo->print.mutex));
	}
	time = get_time();
	if (!check_death)
	{
		printf("%ld : philo %d %s\n", time - philo->arg->time, id, msg);
		ptread_mutex_lock(&(philo->print.mutex));
		philo->print.data = 1;
		pthread_mutex_unlock(&(philo->print.mutex));
	}
}

void	sleepy_time(t_philo *philo)
{
	long int	time;
	long int	sleep;

	time = get_time();
	print("is sleeping", philo, philo->id);
	while (philo->arg->t_sleep > (get_time() - time) && !check_death(philo))
	{
		if (philo->arg->t_sleep - (get_time() - time) > philo->arg->t_die)
			sleep = philo->arg->t_die;
		else
			sleep = philo->arg->t_sleep - (get_time() - time);// "/ 2" ?
		if (check_death(philo))
			return ;
		usleep(sleep);
	}
}

void	timetofeast(t_philo *philo)
{
	long int	time;
	long int	eat;

	time = get_time();
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = time;
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	print("is eating", philo, philo->id);
	while (philo->arg->t_eat > (get_time() - time) )
	{
		if (philo->arg->t_die - (get_time() - time) > philo->arg->t_die)
			eat = philo->arg->t_die;
		else
			eat = philo->arg->t_eat - (get_time() - time); // "/ 2" ?
		usleep(eat);
	}
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
	pthread_mutex_lock(&(philo->dead.mutex));
	if (philo->dead.data == 1)
		tmp = 1;
	pthread_mutex_unlock(&(philo->dead.mutex));
	return (tmp);
}

long int	get_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_full(philo) && !check_death(philo) && (philo->arg->max_eat < 0 || philo->n_eat < philo->arg->max_eat))
	{
		
	}
	return (NULL);
}

void	ft_error(t_env *env, char *s)
{
	printf("%s", s);
	if (env)
	{
		if (env->arg)
			free(env->arg)
		if (env->philos)
			free(env->philos)
		free(env);
	}
	exit(1);
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
		env->philos[i].id = i;
		env->philos[i].n_eat = 0;
	}
	i = -1;
	while (++i < env->arg->n_philo)
	{
		if (env->arg->n_philo == 1)
			env->philos[i].next_fork = NULL;
		else if (i == env->arg->n_philo - 1)
			env->philos[i].next_fork = &env->philos[0].fork;
		else
			env->philos[i].next_fork = &env->philos[i + 1].fork;
	}
	i = -1;
	while (++i < env->arg->n_philo)
		pthread_create(&(env->philos[i].thread), NULL, routine, &(env->philos[i]));
}

void	check_arg(t_env *env, int ac)
{
	if (env->arg->n_philo < 1)
		ft_error(env, "ERROR : Nombre de philos non valide\n");
	if (env->arg->t_die < 0)
		ft_error(env, "ERROR : Time to die non valide\n");
	if (env->arg->t_eat < 0)
		ft_error(env, "ERROR : Time to eat non valide\n");
	if (env->arg->t_sleep < 0)
		ft_error(env, "ERROR : Time to sleep non valide\n");
	if (ac == 6 && env->arg->max_eat < 1)
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
	env->philos = malloc(sizeof(t_philo) * env->arg->n_philo);
	return (env);
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
	printf("init\n");
	env = init_env(env, ac, av);
	if (!env)
		return (1);
	printf("create\n");
	create_philos(env);
}