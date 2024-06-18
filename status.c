/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:05:58 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 14:09:08 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->data->start_time;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex(&philo->data->write_mutex, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !simulation_done(philo->data))
		printf(WHITE"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_done(philo->data))
		printf(WHITE"%-6ld"CYAN" %d is eating\n"RST, elapsed, philo->id);
	else if (status == SLEEPING && !simulation_done(philo->data))
		printf(WHITE"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_done(philo->data))
		printf(WHITE"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	safe_mutex(&philo->data->write_mutex, UNLOCK);
}
