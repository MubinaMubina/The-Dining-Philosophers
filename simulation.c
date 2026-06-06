/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:48:09 by mmubina           #+#    #+#             */
/*   Updated: 2026/06/06 17:48:43 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Sets table->start_time, initializes each philo's last_meal_time to that,
** then creates one pthread per philo (running philo_routine) plus the
** monitor thread. Joins all threads before returning.
** Return 0 on a clean simulation, 1 if any pthread_create fails.
*/
int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
	return (0);
}

/*
** Thread function for each philosopher. Loop until simulation_stopped():
**   1. take_forks  - lock both forks (use lock-ordering or odd/even split
**                    to avoid deadlock); print "has taken a fork" twice
**   2. eat         - lock meal_mutex; update last_meal_time + meals_eaten;
**                    unlock; print "is eating"; precise_sleep_ms(time_to_eat)
**   3. drop_forks  - unlock both forks
**   4. philo_sleep - print "is sleeping"; precise_sleep_ms(time_to_sleep)
**   5. philo_think - print "is thinking" (small sleep helps fairness when
**                    time_to_die is much larger than eat+sleep)
**
** Special case: if num_philos == 1, take the only fork and wait to die.
** Special case: stagger odd ids with a small usleep at start so they don't
**               all race for the same forks at t=0.
**
** Helpers (take_forks, eat, drop_forks, philo_sleep, philo_think) can be
** static functions in this file - but the 42 norm caps each .c file at 5
** functions, so you may want to split them into a separate actions.c.
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	/* edge case: 1 philosopher has only 1 fork, can't ever eat → die */
	if (philo->table->num_philos == 1)
		return (handle_one_philo(philo));
	/* stagger start to reduce contention */
	if (philo->id % 2 == 1)
		usleep(1000);
	while (!simulation_stopped(philo->table))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
