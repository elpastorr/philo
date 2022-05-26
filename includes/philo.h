/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:45:18 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/26 18:18:41 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_philo
{
    int             n;
    int             max_eat;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_t       thread;
}   t_philo;


typedef struct s_env {
    int         t_die;
    int         t_sleep;
    int         t_eat;
    int         n_philo;
    int         max_eat;
    long int    time;
    t_philo     *philos;
}   t_env;

#endif