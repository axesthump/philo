//
// Created by Cave Submarine on 11/11/20.
//
#include "../includes/philo_one.h"

int 	validate_and_parse(char **argv, int argc, t_args *args)
{
	int temp;

	if (argc < 5 || argc > 6)
		return (1);
	if (!(temp = ft_atoi(argv[1])) || ft_atoi(argv[1]) < 1)
		return (2);
	args->num_philo = temp;
	if (!(temp = ft_atoi(argv[2])) || ft_atoi(argv[2]) < 1)
		return (3);
	args->time_to_die = temp;
	if (!(temp = ft_atoi(argv[3])) || ft_atoi(argv[3]) < 1)
		return (4);
	args->time_to_eat = temp;
	if (!(temp = ft_atoi(argv[4])) || ft_atoi(argv[4]) < 1)
		return (5);
	args->time_to_sleep = temp;
	args->num_of_times_each_philo_must_eat = -1;
	if (argc == 6)
	{
		if (!(temp = ft_atoi(argv[5])) || ft_atoi(argv[5]) < 1)
			return (5);
		args->num_of_times_each_philo_must_eat = temp;
	}
	return (0);
}
