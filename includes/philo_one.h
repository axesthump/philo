//
// Created by Cave Submarine on 11/11/20.
//

#ifndef PHILO_PHILO_ONE_H
#define PHILO_PHILO_ONE_H

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct 		s_args
{
	int 			num_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			num_of_times_each_philo_must_eat;
}					t_args;

typedef struct		s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	struct s_table	*table;
	long			last_eat;
	long 			start_sim;
	int 			must_eat;
}					t_philo;

typedef struct 		s_table
{
	t_philo			*philos;
	pthread_mutex_t *forks;
	t_args 			*args;
	pthread_mutex_t change_die;
	pthread_mutex_t try_get_time;
	pthread_mutex_t try_print;
	int 			some_one_die;
}					t_table;

int 				validate_and_parse(char **argv, int argc, t_args *args);
int 				print_error(int err);
int 				init_table(t_table *table, t_args *args);
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
void	 			*life_simulation(void *t);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *s, size_t size);
char				*ft_strjoin(char const *s1, char const *s2, char const *s3,
					char const *s4);
char				*ft_itoa(long n);
long 				get_time(void);



#endif //PHILO_PHILO_ONE_H
