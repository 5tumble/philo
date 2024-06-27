/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:29:41 by rukoltso          #+#    #+#             */
/*   Updated: 2024/06/27 16:30:27 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_print("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_print("The value specified by mutex is invalid");
	else if (EDEADLK == status)
		error_print("A deadlock would occur waiting for the mutex");
	else if (EPERM == status)
		error_print("The current thread does not hold a lock on the mutex");
	else if (ENOMEM == status)
		error_print("Does not have enough memory for another mutex");
	else if (EBUSY == status)
		error_print("The mutex is already locked");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_print("No resources to create thread");
	else if (EPERM == status)
		error_print("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == opcode)
		error_print("The value specified by attr is invalid");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_print("The value specified by thread is not joinable");
	else if (ESRCH == status)
		error_print("No thread could be found by the given thread ID");
	else if (EDEADLK == status)
		error_print("A deadlock was detected");
}

void	safe_thread(pthread_t *thread, void *(*func)(void *), void *arg,
		t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, func, arg), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_print("Error: wrong thread opcode");
}

void	safe_mutex(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_print("Error: wrong mutex opcode");
}
