
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_philo
{
	int N;
	int count;
}   t_philo;

typedef struct s_res
{
	int dead;
}   t_res;

void *CreatePhilo(void *arg)
{
	
	t_philo *my_args;
	t_res *result;
	
	my_args = arg;
	result = malloc(sizeof(t_res));

	printf("philo thread %i running\n", my_args->N);
	fflush(stdout);

	

	result->dead = 0;

	printf("philo thread %i returning\n", my_args->N);
	fflush(stdout);

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

	count = atoi(argv[1]);	/* count is first argument */ 

	thread_ids = (pthread_t *)malloc(sizeof(pthread_t)*count);

	printf("main thread about to create %i philo threads\n", count);
	fflush(stdout);

	for(t=0; t < count; t++) {
		args = malloc(sizeof(t_philo));
		args->N = (t+1);
		args->count = count;
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
	return(0);
}
