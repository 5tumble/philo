/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:50:48 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 15:00:48 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
    long	elapsed;
    long	t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
            &philo->last_meal);
    t_to_die = philo->data->time_to_die;
    if (elapsed > t_to_die)
        return (true);
    return (false);
}

void	*monitor_dinner(void *data)
{
    int		i;
    t_data	*data;

    data = (t_data *)data;
    while (!get_bool(&data->data_mutex, &data->threads_ready))
        ;
    while (!simulation_done(data))
    {
        i = -1;
        while (++i < data->philo_nbr && !simulation_done(data))
        {
            if (philo_died(data->philos + i))
            {
                set_bool(&data->data_mutex, &data->end_time, true);
                write_status(DIED, data->philos + i);
            }
        }
    }
    return (NULL);
}