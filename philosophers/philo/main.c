
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_main
{
	int	count;
	int ttd;
	int tte;
	int tts;
	int ntme;
	int done;
	struct timeval t0;
	pthread_mutex_t plock;
	pthread_mutex_t dlock;

}	t_main;

typedef enum e_fstate 
{
	NOTFREE, 
	FREE, 
}	t_fstate;

typedef struct s_fork
{
	t_fstate state;
	pthread_mutex_t lock;
}	t_fork;

typedef struct s_philo
{
	pthread_t thread_id;
	int count;
	int N;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	size_t ttd;
	int tte;
	int tts;
	int ntme;
	int nmeals;
	int finished;
	int *done;
	struct timeval t0;
	size_t lmeal;
	pthread_mutex_t *plock;
	pthread_mutex_t *dlock;
	pthread_mutex_t finish_lock;
}   t_philo;

int nowsleep(t_philo *my_args);
int think(t_philo *my_args, int time);
int eat(t_philo *my_args, pthread_mutex_t *first, pthread_mutex_t *second);

int try_to_eat(t_philo *my_args);
void *PhiloThread(void *arg);

int init_data(int ac, char **av, t_main *data);
int	check_args(int ac, char **av, t_main *d);
void	make_forks(t_main *data, pthread_mutex_t *forks);
void	make_philo(t_main *data, pthread_mutex_t *forks, t_philo *phs);
int	protect_malloc(t_main *data, pthread_mutex_t *forks, t_philo *philosophers);
void	cleanup(t_main *data, pthread_mutex_t *forks, t_philo *phs);
void	monitor_death(t_main *data, t_philo *philosophers);



int think(t_philo *my_args, int time)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);
	pthread_mutex_lock(my_args->plock);
	pthread_mutex_lock(&my_args->finish_lock);
	if (my_args->finished)
	{
		pthread_mutex_unlock(&my_args->finish_lock);
		pthread_mutex_unlock(my_args->plock);
		return (1);
	}
	pthread_mutex_unlock(&my_args->finish_lock);
	printf("%lu %d is thinking\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	if (!time)
		usleep(200 * (my_args->N % 2));
	else
		usleep(time);
	return (0);
}


int eat(t_philo *my_args, pthread_mutex_t *first, pthread_mutex_t *second)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;

	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);
	pthread_mutex_lock(my_args->dlock);
	my_args->lmeal = elapsed;
	pthread_mutex_unlock(my_args->dlock);

    pthread_mutex_lock(my_args->plock);
	printf("%lu %d is eating\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	my_args->nmeals++;
	if (my_args->ntme && my_args->nmeals >= my_args->ntme)
	{
		//printf("we are here\n");
		pthread_mutex_lock(my_args->dlock);
		if (my_args->nmeals == my_args->ntme)
			(*my_args->done)++;
		pthread_mutex_unlock(my_args->dlock);
		pthread_mutex_lock(&my_args->finish_lock);
		my_args->finished = 1;
		pthread_mutex_unlock(&my_args->finish_lock);
	}
	usleep(my_args->tte * 1000);

	
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	return (0);
}

int try_to_eat(t_philo *my_args)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	t0 = my_args->t0;
	if (my_args->N % 2 == 0)
	{
		first = my_args->left;
		second = my_args->right;
	}
	else
	{
		first = my_args->right;
		second = my_args->left;
	}

	pthread_mutex_lock(first);

	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
	pthread_mutex_lock(&my_args->finish_lock);
	if (my_args->finished)
	{
		pthread_mutex_unlock(&my_args->finish_lock);
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_unlock(&my_args->finish_lock);
	pthread_mutex_lock(my_args->plock);
	printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	if (first == second)
	{
		pthread_mutex_unlock(first);
		usleep(my_args->ttd * 1000);
		return (1);
	}
	pthread_mutex_lock(second);
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);	
	pthread_mutex_lock(my_args->plock);
	pthread_mutex_lock(&my_args->finish_lock);
	if (my_args->finished)			
	{
		pthread_mutex_unlock(&my_args->finish_lock);
		pthread_mutex_unlock(my_args->plock);
		pthread_mutex_unlock(second);	
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_unlock(&my_args->finish_lock);
	printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	return (eat(my_args, first, second));
}

int nowsleep(t_philo *ph)
{
	struct timeval tcurr;
	size_t elapsed;
	
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - ph->t0.tv_sec) * 1000000 + \
				(tcurr.tv_usec - ph->t0.tv_usec);
	pthread_mutex_lock(ph->plock);
	pthread_mutex_lock(&ph->finish_lock);
	if (ph->finished)
	{
		pthread_mutex_unlock(&ph->finish_lock);
		pthread_mutex_unlock(ph->plock);
		return (1);
	}
	pthread_mutex_unlock(&ph->finish_lock);
	printf("%lu %d is sleeping\n", elapsed / 1000, ph->N);
	pthread_mutex_unlock(ph->plock);
	usleep(ph->tts * 1000);
	return (0);
}


void *PhiloThread(void *arg)
{	
	t_philo *ph;
	
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
		if (think(ph, 2000) == 1)
			break ;
	}
	return (NULL);
}

int	check_args(int ac, char **av, t_main *d)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
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
	if (d->count <= 0 || d->ttd <= 0 || d->tte <= 0 || d->tts <= 0 || d->ntme <= 0)
	{
		printf("All arguments must be positive\n");
		return (1);
	}
	if (ac == 5)
		d->ntme = 0;
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

	if (!forks)
		return ;
	t = -1;
	while (++t < data->count)
	{
		args = &phs[t];
		args->N = (t + 1);
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
		pthread_create(&phs[t].thread_id, NULL, PhiloThread, (void *)args);
	}
}

int main(int argc, char **argv)
{
	int t;
	t_main	data;
	t_philo *philosophers;
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

int init_data(int ac, char **av, t_main *data)
{
	if (check_args(ac, av, data) == 1)
		return (1);
	pthread_mutex_init(&data->plock, NULL);
	pthread_mutex_init(&data->dlock, NULL);
	gettimeofday(&data->t0, 0);
	data->done = 0;
	return (0);
}

int	protect_malloc(t_main *data, pthread_mutex_t *forks, t_philo *philosophers)
{
	if (forks && philosophers)
		return (0);
	cleanup(data, forks, philosophers);
	return (1);
}

void	cleanup(t_main *data, pthread_mutex_t *forks, t_philo *phs)
{
	int t;

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
		free(phs);
}

void	monitor_death(t_main *data, t_philo *philosophers)
{
	struct timeval tcurr;
	size_t elapsed;
	int t;
	
	while (1)
	{
		pthread_mutex_lock(&data->dlock);
		if (data->ntme && data->done >= data->count)
		{
			pthread_mutex_unlock(&data->dlock);
			return ;
		}
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec - data->t0.tv_sec) * 1000000 + (tcurr.tv_usec - data->t0.tv_usec);
		t = -1;
		while (++t < data->count)
		{
			if (elapsed - philosophers[t].lmeal >= (size_t)(data->ttd * 1000))
			{
				pthread_mutex_unlock(&data->dlock);
				pthread_mutex_lock(&data->plock);
				printf("%lu %d died\n", elapsed / 1000, t + 1);
				pthread_mutex_unlock(&data->plock);
				return ;
			}
		}
		pthread_mutex_unlock(&data->dlock);
		usleep(15000 / (data->count * 100));
	}
}
