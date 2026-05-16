/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:57:35 by andcardo          #+#    #+#             */
/*   Updated: 2026/05/16 21:30:46 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define ERROR_WRONG_ARG_NR "Invalid input: wrong number of arguments"
# define ERROR_WRONG_CHAR "Invalid input: invalid character"
# define ERROR_WRONG_VAL "Invalid input: invalid value"
# define ERROR_MEMORY_ALLOCATION "Failed to allocate memory"
# define ERROR_MUTEXES_INIT "Failed to initialize mutex"
# define ERROR_THREAD_CREATION "Failed to create thread"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	bool			sim_running;
	pthread_mutex_t	table_lock;
	int				table_mutex_init;
	pthread_mutex_t	print_lock;
	int				print_mutex_init;
	pthread_mutex_t	*forks;
	int				fork_mutex_init;
	int				meal_mutex_init;
	int				threads_created;
	t_philo			*philos;
}	t_table;

int		check_args(t_table *table, int ac, char **av);
int		init_table(t_table *table, int ac, char **av);
void	free_table(t_table *table);
long	ft_atol(const char *s);
long	get_time_ms(void);
void	error_exit(t_table *table, char *message);
int		start_simulation(t_table *table);
void	stop_simulation(t_table *table);
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
void	print_action(t_philo *philo, char *str);
int		is_sim_running(t_table *table);
void	ft_usleep(long time_in_ms, t_table *table);

#endif
