/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre <andcardo@student.42lisboa.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:42:27 by andre             #+#    #+#             */
/*   Updated: 2026/05/17 10:45:08 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_routine(t_philo *philo)
{
	print_action(philo, "is thinking");
	if (philo->table->philo_count % 2 != 0)
		ft_usleep(philo->table->time_to_eat * 2 - philo->table->time_to_sleep, philo->table);
}

