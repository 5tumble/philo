/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:40:12 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 12:43:20 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Very boring but i guess have to manage all the sync stuff
*/

void wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data->mutex, &data->threads_ready))
		;
}