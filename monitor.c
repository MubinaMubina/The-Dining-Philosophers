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
void *monitor_routine(void *arg)
{
	t_table *table;
	int i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (check_death(&table->philos[i]))
			{
				announce_death(table, &table->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(table))
		{
			set_stop_flag(table);
			return (NULL);
		}
		usleep(1000);
	}
}

/*
** Returns 1 if (now - philo->last_meal_time) > table->time_to_die.
** Must lock philo->meal_mutex while reading last_meal_time (data race).
*/
int check_death(t_philo *philo)
{
	long last;
	long now;

	pthread_mutex_lock(&philo->meal_mutex);
	last = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time_ms();
	if (now - last > philo->table->time_to_die)
		return (1);
	return (0);
}

/*
** Returns 1 if must_eat_count is set AND every philo has meals_eaten >= it.
** Must lock each philo's meal_mutex while reading meals_eaten.
*/
int all_ate_enough(t_table *table)
{
	int i;
	int eaten;

	if (table->must_eat_count < 0)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		eaten = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (eaten < table->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}
