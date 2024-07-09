
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int N;
	int count;
	pthread_mutex_t *plock;
	pthread_mutex_t *flock;
	pthread_mutex_t *forks;
}   t_philo;

typedef struct s_res
{
	int dead;
}   t_res;


int	try_to_eat(t_philo *my_args)
{
	int left = my_args->N - 1;
	int right = my_args->N % my_args->count;
	printf("left is %d right is %d\n", left, right);
	if (!pthread_mutex_lock(&my_args->forks[left]))
	{
		if (!pthread_mutex_lock(&my_args->forks[right]))
		{
			printf("philosopher %i is eating\n", my_args->N);
			usleep(100000);
			pthread_mutex_unlock(&my_args->forks[right]);
			pthread_mutex_unlock(&my_args->forks[left]);
			return (1);
		}
		pthread_mutex_unlock(&my_args->forks[left]);
		return (0);
	}
	return (0);
}

void *CreatePhilo(void *arg)
{
	
	t_philo *my_args;
	t_res *result;
  	struct timeval t0;
	struct timeval tcurr;
	long elapsed;
	int hungry = 1;  

	gettimeofday(&t0, 0);
	my_args = arg;
	result = malloc(sizeof(t_res));
	result->dead = 0;

	pthread_mutex_lock(my_args->plock);
	printf("philo thread %i running\n", my_args->N);
	fflush(stdout);
	pthread_mutex_unlock(my_args->plock);

	while (!result->dead)
	{
		if (!hungry)
			usleep(10000);
		else
		{
			if (!try_to_eat(my_args))
				usleep(10000); //think();
			else
				hungry = 0;
		}
		gettimeofday(&tcurr, 0);
		elapsed = (tcurr.tv_sec-t0.tv_sec)*1000000 + tcurr.tv_usec-t0.tv_usec;
		if (elapsed > 5000000)
			result->dead = 1;
	}
	
	pthread_mutex_lock(my_args->plock);
	printf("philo thread %i returning\n", my_args->N);
	fflush(stdout);
	pthread_mutex_unlock(my_args->plock);

    free(my_args);
	return((void *)result);
}

int main(int argc, char **argv)
{
	int t;
	int count;
	t_philo *args;
	t_res *result;
	int err;
	pthread_t *thread_ids;
	pthread_mutex_t lock;
	pthread_mutex_t *forks;

	count = atoi(argv[1]);	/* count is first argument */ 

	thread_ids = malloc(sizeof(pthread_t)*count);
	forks = calloc(count, sizeof(pthread_mutex_t));

	pthread_mutex_init(&lock, NULL);

	for(t=0; t < count; t++) {
		pthread_mutex_init(&forks[t], NULL);
	}

	printf("main thread about to create %i philo threads\n", count);
	fflush(stdout);

	for(t=0; t < count; t++) {
		args = malloc(sizeof(t_philo));
		args->N = (t+1);
		args->count = count;
		args->plock = &lock;
		args->forks = forks;
		printf("main thread creating philo thread %i\n", t+1);
		fflush(stdout);
		err = pthread_create(&(thread_ids[t]), NULL, CreatePhilo, (void *)args);
		printf("main thread has created philo thread %i\n", t+1);
		fflush(stdout);
	}

	for(t=0; t < count; t++) {
		printf("main thread about to join with philo thread %i\n",t+1);
		fflush(stdout);
		err = pthread_join(thread_ids[t],(void **)&result);
		printf("main thread joined with philo thread %i, whose result is %i\n",t+1, result->dead);
		fflush(stdout);
		free(result);
	}

	free(thread_ids);
	free(forks);
	return(0);
}
