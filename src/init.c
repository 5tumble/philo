/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:08 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:08:37 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->left_fork = &forks[(position + 1) % philo_nbr];
	philo->right_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[position];
		philo->right_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		safe_mutex(&philo->philo_mutex, INIT);
		philo->data = data;
		assign_forks(philo, data->forks, i);
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_time = false;
	data->threads_ready = false;
	data->threads_nbr = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		error_print("Malloc error");
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		error_print("Malloc error");
	safe_mutex(&data->write_mutex, INIT);
	safe_mutex(&data->data_mutex, INIT);
	while (++i < data->philo_nbr)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}
