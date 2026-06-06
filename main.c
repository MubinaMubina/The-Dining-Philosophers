/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:47:11 by mmubina           #+#    #+#             */
/*   Updated: 2026/06/06 17:49:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Entry point. Flow:
**   1. Validate + parse arguments into the table.
**   2. Allocate and initialize forks, philos, and mutexes.
**   3. Launch philosopher threads + the monitor thread, then join them.
**   4. Destroy mutexes and free heap allocations.
** Return 0 on a clean run, 1 on any setup or simulation error.
*/
int	main(int ac, char **av)
{
	t_table	table;

	if (parse_args(ac, av, &table) != 0)
		return (1);
	if (init_table(&table) != 0)
		return (1);
	if (start_simulation(&table) != 0)
	{
		cleanup(&table);
		return (1);
	}
	cleanup(&table);
	return (0);
}
