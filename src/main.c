/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcardo <andcardo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:42:41 by andcardo          #+#    #+#             */
/*   Updated: 2026/05/16 18:47:51 by andre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (!check_args(&table, ac, av))
		return (1);
	if (!init_table(&table, ac, av))
		return (1);
	if (start_simulation(&table) != 1)
	{
		free_table(&table);
		return (1);
	}
	free_table(&table);
	return (0);
}
