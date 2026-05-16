/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:34:22 by andcardo          #+#    #+#             */
/*   Updated: 2026/05/16 19:12:59 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *s)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}

int	check_args(t_table *table, int ac, char **av)
{
	int		i;
	long	val;

	if (ac < 5 || ac > 6)
		return (error_exit(table, ERROR_WRONG_ARG_NR), 0);
	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]))
			return (error_exit(table, ERROR_WRONG_CHAR), 0);
		val = ft_atol(av[i]);
		if (i == 1 && (val < 1 || val > 200))
			return (error_exit(table, ERROR_WRONG_VAL), 0);
		if ((i >= 2 && i <= 4) && (val < 60 || val > INT_MAX))
			return (error_exit(table, ERROR_WRONG_VAL), 0);
		if (i == 5 && (val < 0 || val > INT_MAX))
			return (error_exit(table, ERROR_WRONG_VAL), 0);
		i++;
	}
	return (1);
}
