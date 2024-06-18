/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:24:28 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 15:28:41 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_print("Gettimeofday failed!");
	if (time_code == SECOND)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_print("Invalid time code!");
	return (69);
}

void	better_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_print(char *str)
{
	printf(RED "%s\n" RST, str);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_print("Malloc failed!");
	return (ptr);
}

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo = data->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&data->write_mutex, DESTROY);
	safe_mutex(&data->data_mutex, DESTROY);
	free(data->forks);
	free(data->philos);
}
