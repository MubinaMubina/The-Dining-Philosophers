#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				stop_flag;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
}	t_table;

/* parse.c */
int		parse_args(int ac, char **av, t_table *table);
int		ft_atol_positive(const char *s, long *out);

/* init.c */
int		init_table(t_table *table);
int		init_forks(t_table *table);
int		init_philos(t_table *table);

/* simulation.c */
int		start_simulation(t_table *table);
void	*philo_routine(void *arg);

/* monitor.c */
void	*monitor_routine(void *arg);
int		check_death(t_philo *philo);
int		all_ate_enough(t_table *table);

/* utils.c */
long	get_time_ms(void);
void	precise_sleep_ms(long ms, t_table *table);
void	print_status(t_philo *philo, const char *status);
int		simulation_stopped(t_table *table);

/* cleanup.c */
void	cleanup(t_table *table);

#endif
