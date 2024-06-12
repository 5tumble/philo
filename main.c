/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:28:22 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/03 12:38:31 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		error_print("Input is not correct!\n"
			GREEN"Correct is ./philo 5 800 200 200 [5]");
	parse_input(&data, av);
	
	return (0);
}