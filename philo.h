/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:44:29 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/17 14:02:47 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
#include <errno.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RST "\x1B[0m"

typedef enum e_opcodes
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef pthread_mutex_t	t_mutex;

typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_time;
	bool				end;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

//parser.c
void parse_input(t_data *data, char **av);

//helper.c
void error_print(char *str);
void *safe_malloc(size_t size);

//init.c


//safe.c
void safe_thread(pthread_t *thread, void *(*func)(void *), void *arg, t_opcode opcode);
void safe_mutex(t_mutex *mutex, t_opcode opcode);

#endif