/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:05:58 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/24 13:41:34 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status(t_philo_status status, t_philo *philo)
{
    long elapsed;

    elapsed = get_time(MILLISECOND) - philo->data->start_time;
    if (get_bool(&philo->philo_mutex, &philo->full))
        return;
    safe_mutex(&philo->data->write_mutex, LOCK);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
        && !simulation_done(philo->data))
        printf(LIGHT_GRAY "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
    else if (status == EATING && !simulation_done(philo->data))
        printf(LIGHT_GRAY "%-6ld" RST " %d is eating\n", elapsed, philo->id); // Removed CYAN color code
    else if (status == SLEEPING && !simulation_done(philo->data))
        printf(LIGHT_GRAY "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !simulation_done(philo->data))
        printf(LIGHT_GRAY "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
    else if (status == DIED)
        printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
    safe_mutex(&philo->data->write_mutex, UNLOCK);
}