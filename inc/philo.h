/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:57:35 by andcardo          #+#    #+#             */
/*   Updated: 2026/04/07 16:12:59 by andcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
} t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	bool			sim_running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
} t_table;

int		check_args(int ac, char **av);
int		init_table(t_table *table, int ac, char **av);
void	free_table(t_table *table);

#endif
