#include "philo.h"

/*
** Top-level init. Responsibilities:
**   - Set table->stop_flag = 0
**   - Allocate table->forks (N pthread_mutex_t) and table->philos (N t_philo)
**   - Initialize table->stop_mutex and table->print_mutex
**   - Call init_forks() and init_philos()
**   - Set table->start_time = get_time_ms() ONLY right before threads launch
**     (do it in start_simulation, not here, so the clock starts at thread launch)
** Return 0 on success, 1 on allocation/mutex_init failure (cleanup on failure).
*/
int	init_table(t_table *table)
{
	(void)table;
	return (0);
}

/*
** Initializes each of the N fork mutexes in table->forks.
** Return 0 on success, 1 if any pthread_mutex_init fails.
*/
int	init_forks(t_table *table)
{
	(void)table;
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
	(void)table;
	return (0);
}
