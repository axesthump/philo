//
// Created by Cave Submarine on 11/11/20.
//
#include "../includes/philo_one.h"

static int	init_forks(t_table *table, t_args *args)
{
	int i;

	i = -1;
	if (!(table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->num_philo)))
		return (6);
	while (++i < args->num_philo)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return(7);
	}
	return (0);
}

static int 	init_threads(t_table *table, t_args *args)
{
	int i;
	long start;

	if (!(table->philos = (t_philo *)malloc(sizeof(t_philo) * args->num_philo)))
		return (6);
	i = -1;
	start = get_time();
	while (++i < args->num_philo)
	{
		table->philos[i].id = i;
		table->philos[i].left = &(table->forks[i]);
		if (i == 0)
			table->philos[i].right = &(table->forks[args->num_philo - 1]);
		else
			table->philos[i].right = &(table->forks[i - 1]);
		table->philos[i].table = table;
		table->philos[i].start_sim = start;
		pthread_mutex_lock(&(table->try_get_time));
		table->philos[i].last_eat = get_time();
		pthread_mutex_unlock(&(table->try_get_time));
		pthread_create(&(table->philos[i].thread), NULL, life_simulation, &(table->philos[i]));
	}
	return (0);
}

int 		init_table(t_table *table, t_args *args)
{
	int err;

	if ((err = init_forks(table, args)))
		return (err);
	table->some_one_die = 0;
	if (pthread_mutex_init(&(table->change_die), 0) || pthread_mutex_init(&(table->try_get_time), 0) || pthread_mutex_init(&(table->try_print), 0))
		return (7);
	if ((err = init_threads(table, args)))
		return (err);
	return (0);
}