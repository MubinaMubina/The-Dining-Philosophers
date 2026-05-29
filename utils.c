#include "philo.h"

/*
** Returns current time in milliseconds since the epoch.
** Use gettimeofday(&tv, NULL); return tv.tv_sec * 1000 + tv.tv_usec / 1000.
*/
long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
** Sleeps for `ms` milliseconds, but in small usleep increments (e.g. 500us)
** while checking simulation_stopped() so threads can exit promptly.
** usleep alone is inaccurate and can oversleep significantly - don't trust it
** for the whole duration.
*/
void precise_sleep_ms(long ms, t_table *table)
{
	long target;

	target = get_time_ms() + ms;
	while (get_time_ms() < target)
	{
		if (simulation_stopped(table))
			return;
		usleep(500);
	}
}

/*
** Prints "<elapsed_ms> <id> <status>\n" with print_mutex held.
** Must check simulation_stopped() AFTER acquiring print_mutex but BEFORE
** printing - otherwise a state message can be printed after "X died".
** The only exception: the "X died" message itself prints while holding the
** mutex even though stop_flag is being set in the same critical section.
*/
void print_status(t_philo *philo, const char *status)
{
	long elapsed;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (simulation_stopped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return;
	}
	elapsed = get_time_ms() - philo->table->start_time;
	printf("%ld %d %s\n", elapsed, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

/*
** Locks stop_mutex, reads stop_flag, unlocks. Returns the flag value.
** Called constantly from philo_routine and monitor_routine - keep it cheap.
*/
int simulation_stopped(t_table *table)
{
	int stopped;
	pthread_mutex_lock(&table->stop_mutex);
	stopped = table->stop_flag;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stopped);
}

void *handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	precise_sleep_ms(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
