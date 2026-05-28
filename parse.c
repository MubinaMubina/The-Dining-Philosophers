#include "philo.h"

/*
** Validates argc (5 or 6) and parses each argument into table fields.
**   av[1] = num_philos          (must be > 0)
**   av[2] = time_to_die in ms   (must be > 0)
**   av[3] = time_to_eat in ms   (must be > 0)
**   av[4] = time_to_sleep in ms (must be > 0)
**   av[5] = must_eat_count      (optional; >= 0 if given; else set to -1)
** Print an error to stderr on bad input. Return 0 on success, 1 on error.
*/
int	parse_args(int ac, char **av, t_table *table)
{
	(void)ac;
	(void)av;
	(void)table;
	return (0);
}

/*
** Parses a string into a positive long. Rejects:
**   - empty strings
**   - non-digit characters (no '+' / '-' / spaces allowed by the subject)
**   - values that overflow LONG_MAX or are <= 0
** Writes the parsed value to *out. Returns 0 on success, 1 on error.
*/
int	ft_atol_positive(const char *s, long *out)
{
	(void)s;
	(void)out;
	return (0);
}
