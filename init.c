/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:08 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 15:28:46 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(pos + 1) % philo_nbr];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + 1;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = false;
		philo->data = data;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
}

void	data_init(t_data *data)
{
	int i;

	i = 0;
	data->end = false;
	data->threads_ready = false;
	safe_mutex(data->data_mutex, INIT);
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}