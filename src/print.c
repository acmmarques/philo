/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre <andcardo@student.42lisboa.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:20:02 by andre             #+#    #+#             */
/*   Updated: 2026/05/16 21:22:40 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->table->print_lock);
	if (is_sim_running(philo->table))
	{
		time = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
