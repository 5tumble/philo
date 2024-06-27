/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:40:12 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:28:21 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->threads_ready))
		;
}

bool	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

void	unsync_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			better_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
