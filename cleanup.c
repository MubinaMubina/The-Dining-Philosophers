/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:46:51 by mmubina           #+#    #+#             */
/*   Updated: 2026/06/06 17:49:07 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Destroys all initialized mutexes and frees heap allocations.
** Order:
**   1. pthread_mutex_destroy on each fork in table->forks
**   2. pthread_mutex_destroy on each philo's meal_mutex
**   3. pthread_mutex_destroy on table->stop_mutex and table->print_mutex
**   4. free(table->forks); free(table->philos)
** Be defensive: this may be called after a partial init failure, so guard
** against destroying mutexes that were never initialized (track init state
** in init_table, or only call cleanup with fully-initialized tables).
*/
void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}
