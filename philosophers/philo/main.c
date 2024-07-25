/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:18:25 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/25 11:31:09 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				t;
	t_main			data;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;

	if (init_data(argc, argv, &data) == 1)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * data.count);
	make_forks(&data, forks);
	philosophers = malloc(sizeof(t_philo) * data.count);
	if (protect_malloc(&data, forks, philosophers) == 1)
		return (1);
	make_philo(&data, forks, philosophers);
	monitor_death(&data, philosophers);
	t = -1;
	while (++t < data.count)
	{
		pthread_mutex_lock(&philosophers[t].finish_lock);
		philosophers[t].finished = 1;
		pthread_mutex_unlock(&philosophers[t].finish_lock);
	}
	while (--t >= 0)
		pthread_join(philosophers[t].thread_id, NULL);
	cleanup(&data, forks, philosophers);
	return (0);
}

void	make_forks(t_main *data, pthread_mutex_t *forks)
{
	int		t;

	if (!forks)
		return ;
	t = -1;
	while (++t < data->count)
		pthread_mutex_init(&forks[t], NULL);
}

void	make_philo(t_main *data, pthread_mutex_t *forks, t_philo *phs)
{
	t_philo	*args;
	int		t;

	t = -1;
	while (++t < data->count)
	{
		args = &phs[t];
		args->n = (t + 1);
		args->left = &forks[t];
		args->right = &forks[(t + 1) % data->count];
		args->count = data->count;
		args->ttd = (size_t)data->ttd;
		args->tte = data->tte;
		args->tts = data->tts;
		args->ntme = data->ntme;
		args->nmeals = 0;
		args->done = &data->done;
		args->plock = &data->plock;
		args->dlock = &data->dlock;
		args->t0 = data->t0;
		args->lmeal = 0;
		args->finished = 0;
		pthread_mutex_init(&phs[t].finish_lock, NULL);
		pthread_create(&phs[t].thread_id, NULL, philo_thread, (void *)args);
	}
}

void	monitor_death(t_main *data, t_philo *philosophers)
{
	int	t;

	while (1)
	{
		pthread_mutex_lock(&data->dlock);
		if (data->ntme && data->done >= data->count)
		{
			pthread_mutex_unlock(&data->dlock);
			return ;
		}
		t = -1;
		while (++t < data->count)
		{
			if (check_died(data, philosophers, t) == 1)
				return ;
		}
		pthread_mutex_unlock(&data->dlock);
	}
}

int	check_died(t_main *data, t_philo *philosophers, int t)
{
	struct timeval	t0;
	struct timeval	tcurr;
	size_t			elapsed;

	t0 = data->t0;
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - t0.tv_usec);
	if (elapsed - philosophers[t].lmeal >= (size_t)(data->ttd * 1000))
	{
		pthread_mutex_unlock(&data->dlock);
		pthread_mutex_lock(&data->plock);
		printf("%lu %d died\n", elapsed / 1000, t + 1);
		pthread_mutex_unlock(&data->plock);
		return (1);
	}
	return (0);
}
