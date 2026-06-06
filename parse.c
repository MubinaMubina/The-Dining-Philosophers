/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:47:39 by mmubina           #+#    #+#             */
/*   Updated: 2026/06/06 17:48:50 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_int_field(const char *arg, int *dst)
{
	long	val;

	if (ft_atol_positive(arg, &val) != 0)
		return (1);
	*dst = (int)val;
	return (0);
}

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
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n");
		return (1);
	}
	if (parse_int_field(av[1], &table->num_philos) != 0)
		return (1);
	if (ft_atol_positive(av[2], &table->time_to_die) != 0)
		return (1);
	if (ft_atol_positive(av[3], &table->time_to_eat) != 0)
		return (1);
	if (ft_atol_positive(av[4], &table->time_to_sleep) != 0)
		return (1);
	if (ac == 6)
	{
		if (parse_int_field(av[5], &table->must_eat_count) != 0)
			return (1);
	}
	else
		table->must_eat_count = -1;
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
	long	value;
	int		i;

	i = 0;
	value = 0;
	if (!s || !s[0])
		return (1);
	while (s[i])
	{
		if (!(s[i] >= 48 && s[i] <= 57))
			return (1);
		if (value > (LONG_MAX - (s[i] - '0')) / 10)
			return (1);
		value = value * 10 + (s[i] - '0');
		i++;
	}
	if (value <= 0)
		return (1);
	*out = value;
	return (0);
}
