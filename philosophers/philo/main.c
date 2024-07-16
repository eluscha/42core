
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>


typedef enum e_fstate 
{
	NOTFREE, 
	FREE, 
}	t_fstate;


typedef struct s_philo
{
	int N;
	int count;
	size_t ttd;
	int tte;
	int tts;
	int ntme;
	int nmeals;
	int *done;
	int *onedead;
	struct timeval t0;
	size_t *lmeal;
	pthread_mutex_t *plock;
	pthread_mutex_t *dlock;
	pthread_mutex_t *flock;
	pthread_mutex_t *forks;
}   t_philo;

typedef struct s_res
{
	int dead;
}   t_res;


void think(t_philo *my_args) 
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);
    pthread_mutex_lock(my_args->plock);
	printf("%lu %d is thinking\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	usleep(200 * (my_args->N % 2));
}


void eat(t_philo *my_args, int left, int right)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;

	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);

    pthread_mutex_lock(my_args->plock);
	printf("%lu %d is eating\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);

	usleep(my_args->tte * 1000);
	pthread_mutex_unlock(&my_args->forks[right]);
	pthread_mutex_unlock(&my_args->forks[left]);
	*my_args->lmeal = elapsed;
	my_args->nmeals++;
}

int take_forks_eat(t_philo *my_args)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;

	int left = my_args->N - 1;
	int right = my_args->N % my_args->count;

	pthread_mutex_lock(my_args->flock);
	pthread_mutex_lock(&my_args->forks[left]);
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
	pthread_mutex_lock(my_args->plock);
	printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	if (left == right)
	{
		pthread_mutex_unlock(&my_args->forks[left]);
		pthread_mutex_unlock(my_args->flock);
		usleep(10000);
		return (1);
	}
	pthread_mutex_lock(&my_args->forks[right]);
	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
	pthread_mutex_lock(my_args->plock);
	printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
	pthread_mutex_unlock(my_args->plock);
	pthread_mutex_unlock(my_args->flock);
	eat(my_args, left, right);
	return (0);
}



void *PhiloThread(void *arg)
{
	struct timeval t0;
	
	t_philo *my_args;
	struct timeval tcurr;
	size_t elapsed;
	int hungry = 1;

	my_args = arg;

	t0 = my_args->t0;
	think(my_args);

	while (1)
	{
		pthread_mutex_lock(my_args->dlock);
		usleep(100);
		pthread_mutex_unlock(my_args->dlock);
		if (!hungry)
		{
			gettimeofday(&tcurr, 0);
			elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);
			pthread_mutex_lock(my_args->plock);
			printf("%lu %d is sleeping\n", elapsed / 1000, my_args->N);
			pthread_mutex_unlock(my_args->plock);
			usleep(my_args->tts * 1000);
			hungry = 1;
			think(my_args);
			continue ;
		}
		hungry = take_forks_eat(my_args);
		if (my_args->ntme && my_args->nmeals >= my_args->ntme)
		{
			//printf("we are here\n");
			pthread_mutex_lock(my_args->dlock);
			if (my_args->nmeals == my_args->ntme)
				(*my_args->done)++;
			if (*my_args->done == my_args->count)
			{
				pthread_mutex_unlock(my_args->dlock);
				break ;
			}
			pthread_mutex_unlock(my_args->dlock);
		}
	}
    free(my_args);
	return (NULL);
}

/*
test that fails for sure:
 ./philo/philo 5 800 200 200 7
 */

int main(int argc, char **argv)
{
	int t;
	int params[5];
	size_t **lmeals;
	pthread_t *thread_ids;
	pthread_mutex_t *forks;
	t_fstate *forkstates;
	struct timeval t0;

	gettimeofday(&t0, 0);

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
	
	int *done = malloc(sizeof(int));
	*done = 0;

	lmeals = malloc(sizeof(size_t *) * params[0]);
	for(t=0; t < params[0]; t++) {
		lmeals[t] = malloc(sizeof(size_t));
		memset(lmeals[t], 0, sizeof(size_t));
	}

	thread_ids = malloc(sizeof(pthread_t) * params[0]);
	forkstates = malloc(sizeof(forkstates) * params[0]);
	memset(forkstates, NOTFREE, sizeof(forkstates) * params[0]);

	pthread_mutex_t plock;
	pthread_mutex_t dlock;
	pthread_mutex_t flock;

	pthread_mutex_init(&flock, NULL);
	pthread_mutex_init(&plock, NULL);
	pthread_mutex_init(&dlock, NULL);

	forks = malloc(sizeof(pthread_mutex_t) * params[0]);

	for(t=0; t < params[0]; t++) {
		pthread_mutex_init(&forks[t], NULL);
	}

	t_philo *args;

	for(t=0; t < params[0]; t++) {
		args = malloc(sizeof(t_philo));
		args->N = (t+1);
		args->count = params[0];
		args->ttd = (size_t)params[1];
		args->tte = params[2];
		args->tts = params[3];
		args->ntme = params[4];
		args->nmeals = 0;
		args->done = done;
		args->plock = &plock;
		args->dlock = &dlock;
		args->flock = &flock;
		args->forks = forks;
		args->t0 = t0;
		args->lmeal = lmeals[t];
		//printf("main thread creating philo thread %i\n", t+1);
		pthread_create(&(thread_ids[t]), NULL, PhiloThread, (void *)args);
		//printf("main thread has created philo thread %i\n", t+1);
	}
	memset(forkstates, FREE, sizeof(forkstates) * params[0]);
	
	/*
	for(t=0; t < params[0]; t++) {
		pthread_join(thread_ids[t],(void **)&dead);
		if (!dead)
		if (dead)
			unlockp = 1
		printf("main thread joined with philo thread %i, whose result is %i\n",t+1, result->dead);
		free(dead);
	}*/
	struct timeval tcurr;
	size_t elapsed = 0;
	while(1)
	{
		if (params[4] && *done >= params[0])
			break ;
		pthread_mutex_lock(&plock);
		pthread_mutex_lock(&dlock);
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		for(t=0; t < params[0]; t++) {
			if (elapsed - *lmeals[t] >= (size_t)(params[1] * 1000))
			{
				printf("%lu %d died\n", elapsed / 1000, t + 1);
				break ;
			}
		}
		if (t < params[0])
			break ;
		pthread_mutex_unlock(&plock);
		pthread_mutex_unlock(&dlock);
	}

	for(t=0; t < params[0]; t++) {
		pthread_detach(thread_ids[t]);
	}

	usleep(200000);

	if (t < params[0])
	{
		pthread_mutex_unlock(&plock);
		pthread_mutex_unlock(&dlock);
	}
	
    pthread_mutex_destroy(&plock);
    pthread_mutex_destroy(&dlock);
	pthread_mutex_destroy(&flock);
	for(t=0; t < params[0]; t++) {
		pthread_mutex_destroy(&forks[t]);
	}

	free(thread_ids);
	free(forks);
	free(done);
	free(forkstates);
	for(t=0; t < params[0]; t++) {
		free(lmeals[t]);
	}
	free(lmeals);
	return (0);
}
