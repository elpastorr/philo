/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:45:18 by elpastor          #+#    #+#             */
/*   Updated: 2022/06/09 18:26:15 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_mutex {
	long int		data;
	pthread_mutex_t	mutex;
}	t_mutex;


typedef struct s_arg {
	int			t_die;
	int			t_sleep;
	int			t_eat;
	int			n_philo;
	int			max_eat;
}	t_arg;


typedef struct s_philo
{
	int				id;
	int				n_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_t		thread;
	struct s_mutex	last_eat;
	struct s_mutex	print;
	struct s_mutex	full;
	struct s_mutex	dead;
	t_arg			*arg;
}	t_philo;


typedef struct s_env {
	long int	time;
	t_philo		*philos;
	t_arg		*arg;
}	t_env;

#endif