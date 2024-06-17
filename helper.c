/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:24:28 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/17 13:37:48 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_print(char *str)
{
	printf(RED"%s\n"RST, str);
	exit(EXIT_FAILURE);
}

void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_print("Malloc failed!");
	return (ptr);
}
