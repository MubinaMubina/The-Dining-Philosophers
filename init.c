/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:46:56 by mmubina           #+#    #+#             */
/*   Updated: 2026/06/06 17:49:04 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Top-level init. Responsibilities:
**   - Set table->stop_flag = 0
**   - Allocate table->forks (N pthread_mutex_t) and table->philos (N t_philo)
**   - Initialize table->stop_mutex and table->print_mutex
**   - Call init_forks() and init_philos()
**   - Set table->start_time = get_time_ms() ONLY right before threads launch
**     (do it in start_simulation, not here,
	so the clock starts at thread launch)
** Return 0 on success, 1 on allocation/mutex_init failure (cleanup on failure).
*/
/*
** Error path for init_table: destroys the first forks_inited fork mutexes
** (forks_inited stays 0 when forks were never initialized), destroys the
** two table mutexes, frees both arrays (free(NULL) is safe), returns 1.
*/
static int	init_fail(t_table *table, int forks_inited)
{
	int	i;

	i = 0;
	while (i < forks_inited)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
	return (1);
}

int	init_table(t_table *table)
{
	table->stop_flag = 0;
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->stop_mutex);
		return (1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->forks || !table->philos)
		return (init_fail(table, 0));
	if (init_forks(table) != 0)
		return (init_fail(table, 0));
	if (init_philos(table) != 0)
		return (init_fail(table, table->num_philos));
	return (0);
}

/*
** Initializes each of the N fork mutexes in table->forks.
** Return 0 on success, 1 if any pthread_mutex_init fails.
*/
int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Initializes each philo struct:
**   - id (1..N)
**   - meals_eaten = 0, last_meal_time = 0 (will be set to start_time at launch)
**   - meal_mutex initialized
**   - left_fork = &forks[i], right_fork = &forks[(i + 1) % N]
**     (or swap left/right on alternating ids if that's your deadlock strategy)
**   - table back-pointer set
** Return 0 on success, 1 on mutex_init failure.
*/
int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = 0;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		philo->table = table;
		if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].meal_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
