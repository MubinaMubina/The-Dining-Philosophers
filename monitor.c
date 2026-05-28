#include "philo.h"

/*
** Monitor thread. Loops until either a philo dies or everyone has eaten
** must_eat_count times. On each iteration:
**   - For each philo i: call check_death(philo[i])
**     - If dead: lock print_mutex, set stop_flag (under stop_mutex),
**       print "X died", unlock; then return.
**   - If must_eat_count >= 0 and all_ate_enough(table): set stop_flag, return.
**   - Sleep briefly (~1 ms) to keep the 10ms death-report deadline.
*/
void	*monitor_routine(void *arg)
{
	(void)arg;
	return (NULL);
}

/*
** Returns 1 if (now - philo->last_meal_time) > table->time_to_die.
** Must lock philo->meal_mutex while reading last_meal_time (data race).
*/
int	check_death(t_philo *philo)
{
	(void)philo;
	return (0);
}

/*
** Returns 1 if must_eat_count is set AND every philo has meals_eaten >= it.
** Must lock each philo's meal_mutex while reading meals_eaten.
*/
int	all_ate_enough(t_table *table)
{
	(void)table;
	return (0);
}
