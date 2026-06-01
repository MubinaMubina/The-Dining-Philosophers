#include "philo.h"

int	check_death(t_philo *philo)
{
	long	last;
	long	now;

	pthread_mutex_lock(&philo->meal_mutex);
	last = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time_ms();
	if (now - last > philo->table->time_to_die)
		return (1);
	return (0);
}

int	all_ate_enough(t_table *table)
{
	int	i;
	int	eaten;

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

static void	set_stop_flag(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop_flag = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

static void	announce_death(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->print_mutex);
	set_stop_flag(table);
	printf("%ld %d died\n", get_time_ms() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

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
