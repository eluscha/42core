/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:19:16 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/25 11:31:56 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *arg)
{
	t_philo	*ph;

	ph = arg;
	think(ph, 0);
	while (1)
	{
		pthread_mutex_lock(&ph->finish_lock);
		if (ph->finished)
		{
			pthread_mutex_unlock(&ph->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&ph->finish_lock);
		if (try_to_eat(ph) == 1)
			break ;
		if (nowsleep(ph) == 1)
			break ;
		if (ph->tts < ph->tte)
		{
			if (think(ph, (ph->tte - ph->tts) * 1000 + 2000) == 1)
				break ; 
		}
		else if (think(ph, 2000) == 1)
			break ;
	}
	return (NULL);
}

int	think(t_philo *ph, int time)
{
	struct timeval	t0;
	struct timeval	tcurr;
	size_t			elapsed;

	t0 = ph->t0;
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - t0.tv_usec);
	pthread_mutex_lock(&ph->finish_lock);
	if (ph->finished)
	{
		pthread_mutex_unlock(&ph->finish_lock);
		return (1);
	}
	pthread_mutex_unlock(&ph->finish_lock);
	pthread_mutex_lock(ph->plock);
	printf("%lu %d is thinking\n", elapsed / 1000, ph->n);
	pthread_mutex_unlock(ph->plock);
	if (!time)
		usleep(200 * (ph->n % 2));
	else
		usleep(time);
	return (0);
}

int	nowsleep(t_philo *ph)
{
	struct timeval	t0;
	struct timeval	tcurr;
	size_t			elapsed;

	t0 = ph->t0;
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - t0.tv_usec);
	pthread_mutex_lock(ph->plock);
	pthread_mutex_lock(&ph->finish_lock);
	if (ph->finished)
	{
		pthread_mutex_unlock(&ph->finish_lock);
		pthread_mutex_unlock(ph->plock);
		return (1);
	}
	pthread_mutex_unlock(&ph->finish_lock);
	printf("%lu %d is sleeping\n", elapsed / 1000, ph->n);
	pthread_mutex_unlock(ph->plock);
	usleep(ph->tts * 1000);
	return (0);
}
