/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:34:22 by andcardo          #+#    #+#             */
/*   Updated: 2026/03/20 12:43:37 by andcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		// need to check if each arg is numeric
		if (!is_numeric(av[i]))
			return (1);
		// printf("%s\n", av[i]);
		i++;
	}
	// need to check if each arg is greater than 0
	return (0);
}
