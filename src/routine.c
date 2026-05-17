/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre <andcardo@student.42lisboa.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:14:26 by andre             #+#    #+#             */
/*   Updated: 2026/05/17 10:46:26 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_table *table, int i)
{
	long	time;

	time = get_time_ms();
	if (time - table->philos[i].last_meal_time >= table->time_to_die)
	{
		stop_simulation(table);
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n",
			time - table->start_time, table->philos[i].id);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	return (0);
}

static int	monitor_philos(t_table *table)
{
	int	i;
	int	fed;

	i = -1;
	fed = 0;
	while (++i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		if (check_death(table, i))
		{
			pthread_mutex_unlock(&table->philos[i].meal_lock);
			return (1);
		}
		if (table->required_meals != -1
			&& table->philos[i].meals_eaten >= table->required_meals)
			fed++;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
	}
	if (table->required_meals != -1 && fed == table->philo_count)
		return (stop_simulation(table), 1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (monitor_philos(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static void	eat_routine(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->table);
	while (is_sim_running(philo->table))
	{
		think_routine(philo);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (philo->table->philo_count == 1)
		{
			ft_usleep(philo->table->time_to_die, philo->table);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		eat_routine(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep, philo->table);
	}
	return (NULL);
}
