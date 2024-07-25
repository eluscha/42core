/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:19:05 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/25 11:31:44 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat(t_philo *ph)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	struct timeval	tcurr;
	size_t			elapsed;

	if (which_fork_first(ph, &first, &second) == 1)
		return (1);
	if (take_fork(ph, first, NULL) == 1)
		return (1);
	if (take_fork(ph, second, first) == 1)
		return (1);
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - ph->t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - ph->t0.tv_usec);
	pthread_mutex_lock(ph->dlock);
	ph->lmeal = elapsed;
	pthread_mutex_unlock(ph->dlock);
	pthread_mutex_lock(ph->plock);
	printf("%lu %d is eating\n", elapsed / 1000, ph->n);
	pthread_mutex_unlock(ph->plock);
	update_nmeals(ph);
	usleep(ph->tte * 1000);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (0);
}

int	which_fork_first(t_philo *ph, pthread_mutex_t **f, pthread_mutex_t **s)
{
	if (ph->left == ph->right)
	{
		take_fork(ph, ph->left, NULL);
		pthread_mutex_unlock(ph->left);
		usleep(ph->ttd * 1000);
		return (1);
	}
	if (ph->n % 2 == 0)
	{
		*f = ph->left;
		*s = ph->right;
	}
	else
	{
		*f = ph->right;
		*s = ph->left;
	}
	return (0);
}

int	take_fork(t_philo *ph, pthread_mutex_t *fork, pthread_mutex_t *locked)
{
	struct timeval	t0;
	struct timeval	tcurr;
	size_t			elapsed;

	t0 = ph->t0;
	pthread_mutex_lock(fork);
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - t0.tv_usec);
	pthread_mutex_lock(&ph->finish_lock);
	if (ph->finished)
	{
		pthread_mutex_unlock(&ph->finish_lock);
		pthread_mutex_unlock(fork);
		if (locked)
			pthread_mutex_unlock(locked);
		return (1);
	}
	pthread_mutex_unlock(&ph->finish_lock);
	pthread_mutex_lock(ph->plock);
	printf("%lu %d has taken a fork\n", elapsed / 1000, ph->n);
	pthread_mutex_unlock(ph->plock);
	return (0);
}

void	update_nmeals(t_philo *ph)
{
	ph->nmeals++;
	if (!ph->ntme)
		return ;
	if (ph->nmeals != ph->ntme)
		return ;
	pthread_mutex_lock(ph->dlock);
	(*ph->done)++;
	pthread_mutex_unlock(ph->dlock);
}
