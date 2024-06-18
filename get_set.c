/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:32:47 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 15:29:39 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *bol, bool value)
{
	safe_mutex(mutex, LOCK);
	*bol = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *val)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *val;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *val)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *val;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *val, long value)
{
	safe_mutex(mutex, LOCK);
	*val = value;
	safe_mutex(mutex, UNLOCK);
}

bool	simulation_done(t_data *data)
{
	return (get_bool(data->data_mutex, &data->end) == true);
}
