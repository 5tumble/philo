/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:28:22 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:33:03 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 5 && ac != 6)
		error_print(RED "Input is not correct!\n");
	parse_input(&data, av);
	data_init(&data);
	dinner_start(&data);
	clean(&data);
}
