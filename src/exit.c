/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:05:59 by andcardo          #+#    #+#             */
/*   Updated: 2026/05/16 21:31:07 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->threads_created)
		pthread_join(table->philos[i++].thread, NULL);
	i = 0;
	while (i < table->meal_mutex_init)
		pthread_mutex_destroy(&table->philos[i++].meal_lock);
	i = 0;
	while (i < table->fork_mutex_init)
		pthread_mutex_destroy(&table->forks[i++]);
	if (table->table_mutex_init)
		pthread_mutex_destroy(&table->table_lock);
	if (table->print_mutex_init)
		pthread_mutex_destroy(&table->print_lock);
	free(table->philos);
	free(table->forks);
	memset(table, 0, sizeof(t_table));
}

void	error_exit(t_table *table, char *message)
{
	int	len;

	len = 0;
	if (message)
	{
		while (message[len])
			len++;
		write(2, "Error: ", 7);
		write(2, message, len);
		write(2, "\n", 1);
	}
	if (table && table->table_mutex_init)
		stop_simulation(table);
	free_table(table);
}
