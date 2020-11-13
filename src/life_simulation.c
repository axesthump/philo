//
// Created by Cave Submarine on 11/12/20.
//
#include "../includes/philo_one.h"

long get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void my_wait(long ms)
{
	long start;

	start = get_time();
	while(get_time() - start < ms)
		usleep(10);
}

char 		*get_row(long ms, int id, char *str)
{
	char *s_ms;
	char *s_id;
	char *res;

	s_ms = ft_itoa(ms);
	s_id = ft_itoa((long) (id + 1));
	if (!(res = ft_strjoin(s_ms, " ", s_id, str)))
		return (0);
	free(s_ms);
	free(s_id);
	return (res);
}

void 		print(char **str, int some_on_die, t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->try_print));
	if (!some_on_die)
		ft_putstr_fd(*str, 1);
	pthread_mutex_unlock(&(philo->table->try_print));
	free(*str);
}

int 		take_fork(t_philo *philo, long start, pthread_mutex_t *fork_1, pthread_mutex_t *fork_2)
{
	char *str;

	pthread_mutex_lock(fork_1);
	if (!(str = get_row(get_time() - start, philo->id, " has taken a fork\n")))
		return (6);
	print(&str, philo->table->some_one_die, philo);
	pthread_mutex_lock(fork_2);
	if (!(str = get_row(get_time() - start, philo->id, " has taken a fork\n")))
		return (6);
	print(&str, philo->table->some_one_die, philo);
	return (0);
}

void 		put_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

int 		eat(t_philo *philo, long start)
{
	char *str;

	if ((philo->id) % 2 == 0)
		take_fork(philo, start, philo->left, philo->right);
	else
		take_fork(philo, start, philo->right, philo->left);
	pthread_mutex_lock(&(philo->table->try_get_time));
	if (!(str = get_row(get_time() - start, philo->id, " is eating\n")))
		return (6);
	pthread_mutex_unlock(&(philo->table->try_get_time));
	pthread_mutex_lock(&(philo->table->try_get_time));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->table->try_get_time));
	print(&str, philo->table->some_one_die, philo);
	my_wait(philo->table->args->time_to_eat);
	if ((philo->id) % 2 == 0)
		put_forks(philo->right, philo->left);
	else
		put_forks(philo->left, philo->right);
	return (0);
}

int 		sleeping(t_philo *philo, long start)
{
	char *str;

	pthread_mutex_lock(&(philo->table->try_get_time));
	if (!(str = get_row(get_time() - start, philo->id, " is sleeping\n")))
		return (6);
	pthread_mutex_unlock(&(philo->table->try_get_time));
	print(&str, philo->table->some_one_die, philo);
	my_wait(philo->table->args->time_to_sleep);
	return (0);
}

int			thinking(t_philo *philo, long start)
{
	char *str;

	pthread_mutex_lock(&(philo->table->try_get_time));
	if (!(str = get_row(get_time() - start, philo->id, " is thinking\n")))
		return (6);
	pthread_mutex_unlock(&(philo->table->try_get_time));
	print(&str, philo->table->some_one_die, philo);
	return (0);
}

void 		*print_die_msg(t_philo *philo)
{
	char 	*msg;

	pthread_mutex_unlock(&(philo->table->try_get_time));
	pthread_mutex_lock(&(philo->table->try_get_time));
	if (!(msg = get_row(get_time() - philo->start_sim, philo->id, " died\n")))
		return (philo);
	pthread_mutex_unlock(&(philo->table->try_get_time));
	pthread_mutex_lock(&(philo->table->change_die));
	print(&msg, philo->table->some_one_die, philo);
	philo->table->some_one_die = 1;
	pthread_mutex_unlock(&(philo->table->change_die));
	return (0);
}

void 		*time_to_die(void *t)
{
	t_philo *philo;

	philo = (t_philo *)t;
	while (1)
	{
		pthread_mutex_lock(&(philo->table->try_get_time));
		if (get_time() - philo->last_eat > philo->table->args->time_to_die)
			break;
		if (!philo->must_eat)
		{
			pthread_mutex_unlock(&(philo->table->try_get_time));
			return (0);
		}
		pthread_mutex_unlock(&(philo->table->try_get_time));
	}
	return (print_die_msg(philo));
}

void 		start_sim(t_philo *philo)
{
	while(philo->must_eat)
	{
		if (philo->table->some_one_die)
			break;
		if (eat(philo, philo->start_sim))
		{
			print_error(6);
			break;
		}
		if (philo->table->some_one_die)
			break;
		if (sleeping(philo, philo->start_sim))
		{
			print_error(6);
			break;
		}
		if (philo->table->some_one_die)
			break;
		if (thinking(philo, philo->start_sim))
		{
			print_error(6);
			break;
		}
		--philo->must_eat;
	}
}

void	 	*life_simulation(void *t)
{
	t_philo 	*philo;
	pthread_t	time_die;

	philo = (t_philo *)t;
	pthread_create(&time_die, 0, time_to_die, philo);
	philo->must_eat = philo->table->args->num_of_times_each_philo_must_eat;
	start_sim(philo);
	pthread_join(time_die, 0);
	return (0);
}