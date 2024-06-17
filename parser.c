/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:28:36 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/03 12:36:42 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	./philo 5 800 200 200
	1)numbers
	2)not > INT_MAX
	3)timestampls > 60 ms
*/

#include "philo.h"

static bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int parser(const char *av)
{
	int len;
	const char *num;

	len = 0;
	while(is_space(*av))
		av++;
	if (*av == '-')
		error_print("Error: negative numbers");
	else if (*av == '+')
		av++;
	if (!is_digit(*av))
		error_print("Error: wrong argument");
	num = av;
	if (len > 10)
		error_print("Error: number is too big");
	return (num);
}

static long my_atol (char *str)
{
	long num;
	int i;

	num = 0;
	i = 0;
	str = parser(str);
	while (is_digit(str[i]))
		num = (num * 10) + (str[i++] - '0');
	if (num > INT_MAX)
		error_print("Error: number is too big");
	return (num);
}

//1e3 conversion to ms

void parse_input(t_data *data, char **av)
{
	data->philo_nbr = my_atol(av[1]);
	data->time_to_die = my_atol(av[2]) * 1e3;
	data->time_to_eat = my_atol(av[3]) * 1e3;
	data->time_to_sleep = my_atol(av[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 || data->time_to_sleep < 6e4)
		error_print("Error: timestamps must be > 60 ms");
	if (av[5])
		data->nbr_limit_meals = my_atol(av[5]);
	else
		data->nbr_limit_meals = -1;
}

