/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:07:53 by andcardo          #+#    #+#             */
/*   Updated: 2026/05/16 20:09:16 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_memory(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
	{
		free(table->philos);
		return (0);
	}
	return (1);
}

static int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->table_lock, NULL) != 0)
		return (0);
	table->table_mutex_init++;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	table->print_mutex_init++;
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		table->fork_mutex_init++;
		if (pthread_mutex_init(&table->philos[i].meal_lock, NULL) != 0)
			return (0);
		table->meal_mutex_init++;
		i++;
	}
	return (1);
}

static void	assign_forks(t_table *table, int i)
{
	if (table->philos[i].id % 2 == 0)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->philo_count];
	}
	else
	{
		table->philos[i].left_fork = &table->forks[(i + 1)
			% table->philo_count];
		table->philos[i].right_fork = &table->forks[i];
	}
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].table = table;
		assign_forks(table, i);
		i++;
	}
	return (1);
}

int	init_table(t_table *table, int ac, char **av)
{
	table->philo_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->required_meals = -1;
	if (ac == 6)
		table->required_meals = ft_atol(av[5]);
	table->sim_running = 1;
	table->start_time = get_time_ms();
	if (!allocate_memory(table))
		return (error_exit(table, ERROR_MEMORY_ALLOCATION), 0);
	if (!init_mutexes(table))
		return (error_exit(table, ERROR_MUTEXES_INIT), 0);
	init_philos(table);
	return (1);
}
