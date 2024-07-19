
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
	t_fork *left;
	t_fork *right;
	size_t ttd;
	int tte;
	int tts;
	int ntme;
	int nmeals;
	int *done;
	struct timeval t0;
	size_t lmeal;
	pthread_mutex_t *plock;
	pthread_mutex_t *dlock;
	pthread_mutex_t *flock;
	pthread_mutex_t *forks;
}   t_philo;


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


void eat(t_philo *my_args, t_fork *first, t_fork *second)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;

	gettimeofday(&tcurr, 0);
	elapsed = (tcurr.tv_sec - t0.tv_sec) * 1000000 + (tcurr.tv_usec - t0.tv_usec);
	my_args->lmeal = elapsed;
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
	}
	usleep(my_args->tte * 1000);
	first->state = FREE;
	second->state = FREE;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&second->lock);
}

int take_forks_eat(t_philo *my_args)
{
	struct timeval t0;
	struct timeval tcurr;
	size_t elapsed;

	t0 = my_args->t0;

	//gettimeofday(&tcurr, 0);
	//elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
	//printf("%lu %d is trying\n", elapsed, my_args->N);
	
	if (my_args->left == my_args->right)
	{	
		usleep(10000);
		return (1);
	}

	t_fork *first;
	t_fork *second;
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

	if (first->state && second->state)
	{
		pthread_mutex_lock(&first->lock);
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		first->state = NOTFREE;
		pthread_mutex_lock(my_args->plock);
		printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
		pthread_mutex_unlock(my_args->plock);
	
		pthread_mutex_lock(&second->lock);
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		second->state = NOTFREE;
		pthread_mutex_lock(my_args->plock);
		printf("%lu %d has taken a fork\n", elapsed / 1000, my_args->N);
		pthread_mutex_unlock(my_args->plock);
		eat(my_args, first, second);
		return 0;
	}
	return (1);
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
		//pthread_mutex_lock(my_args->dlock);
		//pthread_mutex_unlock(my_args->dlock);
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
		if (hungry)
			continue ;
	}
	return (NULL);
}

int	check_args(int ac, char **av, int *params)
{
	int	t;
	int	val;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	t = 0;
	while (t < ac - 1)
	{
		val = atoi(av[t + 1]);
		if (val <= 0)
		{
			printf("All arguments have to be positive\n");
			return (1);
		}
		params[t] = val;
		t++;
	}
	if (t == 4)
		params[t] = 0;
	return (0);
}




int main(int argc, char **argv)
{
	int t;

	int done = 0;
	int params[5];
	t_philo *philosophers;
	struct timeval t0;

	gettimeofday(&t0, 0);
	
	if (check_args(argc, argv, params) == 1)
		return (1);
	

	pthread_mutex_t plock;
	pthread_mutex_t dlock;

	pthread_mutex_init(&plock, NULL);
	pthread_mutex_init(&dlock, NULL);

	t_fork *forks = malloc(sizeof(t_fork) * params[0]);
	for(t=0; t < params[0]; t++) {
		pthread_mutex_init(&forks[t].lock, NULL);
		forks[t].state = FREE;
	}

	

	philosophers = malloc(sizeof(t_philo) * params[0]);

	t_philo *args;

	for(t=0; t < params[0]; t++) {
		args = &philosophers[t];   // this is so far not freed
		args->N = (t+1);
		args->left = &forks[t];
		args->right = &forks[(t + 1) % params[0]];
		args->count = params[0];
		args->ttd = (size_t)params[1];
		args->tte = params[2];
		args->tts = params[3];
		args->ntme = params[4];
		args->nmeals = 0;
		args->done = &done;
		args->plock = &plock;
		args->dlock = &dlock;
		args->t0 = t0;
		args->lmeal = 0;
		pthread_create(&(philosophers[t].thread_id), NULL, PhiloThread, (void *)args);
	}

	struct timeval tcurr;
	size_t elapsed = 0;
	while(1)
	{
		if (params[4] && done >= params[0])
			break ;
		pthread_mutex_lock(&plock);
		pthread_mutex_lock(&dlock);
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + (tcurr.tv_usec-t0.tv_usec);
		for(t=0; t < params[0]; t++) {
			if (elapsed - philosophers[t].lmeal >= (size_t)(params[1] * 1000))
			{
				printf("%lu %d died\n", elapsed / 1000, t + 1);
				break ;
			}
		}
		if (t < params[0])
			break ;
		pthread_mutex_unlock(&plock);
		pthread_mutex_unlock(&dlock);
		usleep(15000);
	}

	for(t=0; t < params[0]; t++) {
		pthread_detach(philosophers[t].thread_id);
	}

	usleep(200000);

	if (t < params[0])
	{
		pthread_mutex_unlock(&plock);
		pthread_mutex_unlock(&dlock);
	}
	
    pthread_mutex_destroy(&plock);
    pthread_mutex_destroy(&dlock);
	for(t=0; t < params[0]; t++) {
		pthread_mutex_destroy(&forks[t].lock);
	}

	free(philosophers);
	//free(done);
	free(forks);
	return (0);
}
