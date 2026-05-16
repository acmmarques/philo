/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre <andcardo@student.42lisboa.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:57:38 by andre             #+#    #+#             */
/*   Updated: 2026/05/16 21:23:52 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_running(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->table_lock);
	status = table->sim_running;
	pthread_mutex_unlock(&table->table_lock);
	return (status);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->table_lock);
	table->sim_running = 0;
	pthread_mutex_unlock(&table->table_lock);
}

static int	init_threads_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_routine, &table->philos[i]) != 0)
			return (0);
		table->threads_created++;
		i++;
	}
	return (1);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;

	if (!init_threads_philos(table))
		return (error_exit(table, ERROR_THREAD_CREATION), 0);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, table) != 0)
		return (error_exit(table, ERROR_THREAD_CREATION), 0);
	pthread_join(monitor_thread, NULL);
	return (1);
}
