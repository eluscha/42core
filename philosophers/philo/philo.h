/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:56:33 by eusatiko          #+#    #+#             */
/*   Updated: 2024/07/25 11:52:43 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
	int				count;
	int				ttd;
	int				tte;
	int				tts;
	int				ntme;
	int				done;
	struct timeval	t0;
	pthread_mutex_t	plock;
	pthread_mutex_t	dlock;
}	t_main;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				count;
	int				n;
	size_t			ttd;
	int				tte;
	int				tts;
	int				ntme;
	int				nmeals;
	int				finished;
	int				*done;
	struct timeval	t0;
	size_t			lmeal;
	pthread_mutex_t	*plock;
	pthread_mutex_t	*dlock;
	pthread_mutex_t	finish_lock;
}	t_philo;

/*main*/
void	make_forks(t_main *data, pthread_mutex_t *forks);
void	make_philo(t_main *data, pthread_mutex_t *forks, t_philo *phs);
void	monitor_death(t_main *data, t_philo *philosophers);
int		check_died(t_main *data, t_philo *philosophers, int t);
/*philo_thread*/
void	*philo_thread(void *arg);
int		think(t_philo *my_args, int time);
int		nowsleep(t_philo *my_args);
/*philo_eat*/
int		try_to_eat(t_philo *my_args);
int		which_fork_first(t_philo *ph, pthread_mutex_t **f, pthread_mutex_t **s);
int		take_fork(t_philo *ph, pthread_mutex_t *fork, pthread_mutex_t *locked);
void	update_nmeals(t_philo *ph);
/*utils*/
int		init_data(int ac, char **av, t_main *data);
int		check_args(int ac, char **av, t_main *d);
int		protect_malloc(t_main *data, pthread_mutex_t *forks, t_philo *phs);
void	cleanup(t_main *data, pthread_mutex_t *forks, t_philo *phs);

#endif
