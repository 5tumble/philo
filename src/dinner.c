/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:48:28 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:30:51 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	better_usleep(t_think * 0.42, philo->data);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_nbr);
	write_status(TAKE_LEFT_FORK, philo);
	while (!simulation_done(philo->data))
		better_usleep(200, philo->data);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo);
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	better_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->min_meals_counter > 0
		&& philo->meals_counter == philo->data->min_meals_counter)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->left_fork->fork, UNLOCK);
	safe_mutex(&philo->right_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_nbr);
	unsync_philos(philo);
	while (!simulation_done(philo->data))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		better_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->min_meals_counter == 0)
		return ;
	else if (data->philo_nbr == 1)
		safe_thread(&data->philos[0].thread_id, lone_philo, &data->philos[0],
			CREATE);
	else
	{
		while (++i < data->philo_nbr)
			safe_thread(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	}
	safe_thread(&data->monitor, monitor_dinner, data, CREATE);
	data->start_time = get_time(MILLISECOND);
	set_bool(&data->data_mutex, &data->threads_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->data_mutex, &data->end_time, true);
	safe_thread(&data->monitor, NULL, NULL, JOIN);
}
