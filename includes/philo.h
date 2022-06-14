/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:45:18 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/14 19:15:25 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex {
	long int		data;
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_arg {
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				n_philo;
	int				max_eat;
	long int		time;
	pthread_mutex_t	print;
	struct s_mutex	dead;
}	t_arg;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_t		thread;
	struct s_mutex	last_eat;
	struct s_mutex	full;
	t_arg			*arg;
}	t_philo;

typedef struct s_env {
	t_philo		*philos;
	t_arg		*arg;
}	t_env;

t_env		*init_env(t_env *env, int ac, char **av);
void		main_thread(t_env *env);
void		dead_thread(t_env *env, int i);

void		*routine(void *arg);
void		print(char *msg, t_philo *philo, int id);
void		lets_eat(t_philo *philo);
void		sleepy_time(t_philo *philo);
void		timetofeast(t_philo *philo);

void		check_arg(t_env *env, int ac);
int			check_death(t_philo *philo);
int			check_full(t_philo *philo);
int			check_all_full(t_env *env);

void		launch_pilos(t_env *env);
void		create_philos(t_env *env);
void		shut_philos(t_env *env);
void		ft_error(t_env *env, char *s);

void		ft_usleep(t_philo *philo, long int wait, long int time);
long int	get_time(void);
int			ft_atoi(const char *nbr);

#endif