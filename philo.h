/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:44:29 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/18 15:28:32 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
}						t_opcode;

enum					e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,

}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

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
	t_mtx				philo_mutex;
}						t_philo;

typedef struct s_data
{
	bool				threads_ready;
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_time;
	bool				end_time;
	long				min_meals;
	t_fork				*forks;
	t_philo				*philos;
	t_mutex				data_mutex;
	pthread_t			monitor;
}						t_data;

// parser.c
void					parse_input(t_data *data, char **av);

// helper.c
void					error_print(char *str);
void					*safe_malloc(size_t size);
long					get_time(t_time_code time_code);
void					better_usleep(long usec, t_data *data);
void					clean(t_data *data);

// init.c
void					data_init(t_data *data);

// safe.c
void					safe_thread(pthread_t *thread, void *(*func)(void *),
							void *arg, t_opcode opcode);
void					safe_mutex(t_mutex *mutex, t_opcode opcode);

// get_set.c
void					set_bool(t_mtx *mutex, bool *bol, bool value);
bool					get_bool(t_mtx *mutex, bool *val);
long					get_long(t_mtx *mutex, long *val);
void					set_long(t_mtx *mutex, long *val, long value);
bool					simulation_done(t_data *data);

// status.c
void					write_status(t_status status, t_philo *philo);

// sync.c
void					wait_all_threads(t_data *data);
void					increase_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					unsync_philos(t_philo *philo);

// monitor.c
void					*monitor_dinner(void *data);

#endif