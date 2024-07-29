/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:18:49 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/25 11:18:53 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_main *data)
{
	if (check_args(ac, av, data) == 1)
		return (1);
	pthread_mutex_init(&data->plock, NULL);
	pthread_mutex_init(&data->dlock, NULL);
	gettimeofday(&data->t0, 0);
	data->done = 0;
	return (0);
}

int	check_args(int ac, char **av, t_main *d)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	d->count = atoi(av[1]);
	d->ttd = atoi(av[2]);
	d->tte = atoi(av[3]);
	d->tts = atoi(av[4]);
	if (ac == 6)
		d->ntme = atoi(av[5]);
	else
		d->ntme = 1;
	if (d->count <= 0 || d->ttd <= 0 || d->tte <= 0 || \
		d->tts <= 0 || d->ntme <= 0)
	{
		printf("All arguments must be positive\n");
		return (1);
	}
	if (ac == 5)
		d->ntme = 0;
	return (0);
}

int	protect_malloc(t_main *data, pthread_mutex_t *forks, t_philo *phs)
{
	if (forks && phs)
		return (0);
	cleanup(data, forks, phs);
	return (1);
}

void	cleanup(t_main *data, pthread_mutex_t *forks, t_philo *phs)
{
	int	t;

	pthread_mutex_destroy(&data->plock);
	pthread_mutex_destroy(&data->dlock);
	if (forks)
	{
		t = -1;
		while (++t < data->count)
			pthread_mutex_destroy(&forks[t]);
		free(forks);
	}
	if (phs)
	{
		t = -1;
		while (++t < data->count)
			pthread_mutex_destroy(&phs[t].finish_lock);
		free(phs);
	}
}
