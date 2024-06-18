/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:16:22 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 14:45:25 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
    safe_mutex(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo);
    safe_mutex(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo);
    set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
    philo->meals_counter++;
    write_status(EATING, philo);
    better_usleep(philo->data->time_to_eat, philo->data);
    if (philo->data->nbr_limit_meals > 0
        && philo->meals_counter == philo->data->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex(&philo->first_fork->fork, UNLOCK);
    safe_mutex(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
    t_philo	*philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->data);
    set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
    while (!simulation_done(philo->data))
    {
        if (get_bool(&philo->philo_mutex, &philo->full))
            break ;
        eat(philo);
        write_status(SLEEPING, philo);
        better_usleep(philo->data->time_to_sleep, philo->data);
        write_status(THINKING, philo);
    }
    return (NULL);
}

void dinner_start(t_data *data)
{
    int i;

    i = 0;
    if (data->nbr_limit_meals == 0)
        return ;
    else if (data->philo_nbr == 1)
        safe_thread(&data->philos[0].thread_id, dinner_simulation, &data->philos[0], CREATE);
    else
    {
        while (i < data->philo_nbr)
        {
            safe_thread(&data->philos[i].thread_id, dinner_simulation, &data->philos[i], CREATE);
            i++;
        }
    }
    data->start_time = get_time(MILLISECOND);
    set_bool(&data->data_mutex, &data->threads_ready, true);
    i = 0;
    while (i < data->philo_nbr)
        safe_thread(&data->philos[i++].thread_id, NULL, NULL, JOIN);
}