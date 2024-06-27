/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:28:36 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:28:10 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*valid_input(char *str)
{
	int		len;
	char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_print("No Negative numbers!");
	if (!is_digit(*str))
		error_print("Input is not a digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_print("Number is to big");
	return (number);
}

static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_print("Number is to big");
	return (num);
}

void	parse_input(t_data *data, char *input[])
{
	data->philo_nbr = ft_atol(input[1]);
	data->time_to_die = ft_atol(input[2]) * 1e3;
	data->time_to_eat = ft_atol(input[3]) * 1e3;
	data->time_to_sleep = ft_atol(input[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_print("Timestamps have to be bigger than 60ms");
	if (input[5])
		data->min_meals_counter = ft_atol(input[5]);
	else
		data->min_meals_counter = -1;
}
