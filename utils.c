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
	(void)ms;
	(void)table;
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
	(void)philo;
	(void)status;
}

/*
** Locks stop_mutex, reads stop_flag, unlocks. Returns the flag value.
** Called constantly from philo_routine and monitor_routine - keep it cheap.
*/
int simulation_stopped(t_table *table)
{
	(void)table;
	return (0);
}
