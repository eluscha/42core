
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int N;
	int count;
	int ttd;
	int tte;
	int tts;
	int ntme;
	int nmeals;
	int *done;
	int *onedead;
	pthread_mutex_t *plock;
	pthread_mutex_t *dlock;
	pthread_mutex_t *forks;
}   t_philo;

typedef struct s_res
{
	int dead;
}   t_res;


int	try_to_eat(t_philo *my_args, struct timeval t0, unsigned long *lma)
{
	unsigned long elapsed;
	struct timeval tcurr;
	int left = my_args->N - 1;
	int right = my_args->N % my_args->count;
	//printf("philo num %d tries to eat\n", my_args->N);
	if (!pthread_mutex_lock(&my_args->forks[left]))
	{
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		pthread_mutex_lock(my_args->plock);
		printf("%lu %d has taken a left fork\n", elapsed / 1000, my_args->N);
		pthread_mutex_unlock(my_args->plock);
		if (!pthread_mutex_lock(&my_args->forks[right]))
		{
			gettimeofday(&tcurr, 0);
			elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
			pthread_mutex_lock(my_args->plock);
			printf("%lu %d has taken a right fork\n", elapsed / 1000, my_args->N);
			printf("%lu %d is eating\n", elapsed / 1000, my_args->N);
			pthread_mutex_unlock(my_args->plock);
			usleep(my_args->tte * 1000);
			pthread_mutex_unlock(&my_args->forks[right]);
			pthread_mutex_unlock(&my_args->forks[left]);
			*lma = elapsed;
			my_args->nmeals++;
			return (1);
		}
		printf("cannot get the right one\n");
		pthread_mutex_unlock(&my_args->forks[left]);
		return (0);
	}
	return (0);
}

void *PhiloThread(void *arg)
{
	
	t_philo *my_args;
  	struct timeval t0;
	struct timeval tcurr;
	unsigned long elapsed;
	unsigned long lastmeal;
	int hungry = 1;  

	gettimeofday(&t0, 0);
	my_args = arg;

	while (1)
	{
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		if (elapsed - lastmeal >= my_args->ttd * 1000)
		{
			pthread_mutex_lock(my_args->plock);
			printf("%lu %d died\n", elapsed / 1000, my_args->N);
			*my_args->onedead = 1;
			free(my_args);
			return ((void *)1);
		}
		if (!hungry)
		{
			pthread_mutex_lock(my_args->plock);
			printf("%lu %d is sleeping\n", elapsed / 1000, my_args->N);
			pthread_mutex_unlock(my_args->plock);
			hungry = 1;
			usleep(my_args->tts * 1000);
			pthread_mutex_lock(my_args->plock);
			printf("%lu %d is thinking\n", elapsed / 1000 + my_args->tts, my_args->N);
			pthread_mutex_unlock(my_args->plock);
			usleep(1000);
			continue ;
		}
		if (!try_to_eat(my_args, t0, &lastmeal))
			continue ;
		hungry = 0;
		if (my_args->ntme && my_args->nmeals >= my_args->ntme)
		{
			//printf("we are here\n");
			pthread_mutex_lock(my_args->dlock);
			if (my_args->nmeals == my_args->ntme)
				(*my_args->done)++;
			if (*my_args->done == my_args->count)
			{
				pthread_mutex_unlock(my_args->dlock);
				free(my_args);
				return (NULL);
			}
			pthread_mutex_unlock(my_args->dlock);
		}
	}
    free(my_args);
	return (NULL);
}

int main(int argc, char **argv)
{
	int t;
	int params[5];
	t_philo *args;
	int *onedead;
	int err;
	pthread_t *thread_ids;
	pthread_mutex_t plock;
	pthread_mutex_t dlock;
	pthread_mutex_t *forks;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	t = 0;
	while (t < argc - 1)
	{
		params[t] = atoi(argv[t + 1]);
		if (params[t] <= 0)
		{
			printf("All arguments have to be positive\n");
			return (1);
		}
		t++;
	}
	if (t == 4)
		params[t] = 0;
	onedead = malloc(sizeof(int));
	*onedead = 0;
	int *done = malloc(sizeof(int));
	*done = 0; 
	thread_ids = malloc(sizeof(pthread_t) * params[0]);
	forks = calloc(params[0], sizeof(pthread_mutex_t)); // can use malloc and memset..

	pthread_mutex_init(&plock, NULL);
	pthread_mutex_init(&dlock, NULL);
	for(t=0; t < params[0]; t++) {
		pthread_mutex_init(&forks[t], NULL);
	}

	for(t=0; t < params[0]; t++) {
		args = malloc(sizeof(t_philo));
		args->N = (t+1);
		args->count = params[0];
		args->ttd = params[1];
		args->tte = params[2];
		args->tts = params[3];
		args->ntme = params[4];
		args->nmeals = 0;
		args->done = done;
		args->onedead = onedead;
		args->plock = &plock;
		args->dlock = &dlock;
		args->forks = forks;
		//printf("main thread creating philo thread %i\n", t+1);
		err = pthread_create(&(thread_ids[t]), NULL, PhiloThread, (void *)args);
		//printf("main thread has created philo thread %i\n", t+1);
	}

	
	/*
	for(t=0; t < params[0]; t++) {
		pthread_join(thread_ids[t],(void **)&dead);
		if (!dead)
		if (dead)
			unlockp = 1
		printf("main thread joined with philo thread %i, whose result is %i\n",t+1, result->dead);
		free(dead);
	}*/

	if (params[4])
	{
		while ( !(*onedead) && *done < params[0])
		{
			//printf("params[4] is %d\n", params[4]);
			usleep(1000);
			continue ;
		}
	}
	else
	{
		while (!(*onedead))
		{
			//printf("params[4] is %d\n", params[4]);
			usleep(1000);
			continue ;
		}
	}
	
	for(t=0; t < params[0]; t++) {
		pthread_detach(thread_ids[t]);
	}

	usleep(2000000);

	if (*onedead)
		pthread_mutex_unlock(&plock);
    pthread_mutex_destroy(&plock);
    pthread_mutex_destroy(&dlock);
	for(t=0; t < params[0]; t++) {
		pthread_mutex_destroy(&forks[t]);
	}

	free(thread_ids);
	free(forks);
	free(done);
	free(onedead);
	return (0);
}
