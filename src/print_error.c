//
// Created by Cave Submarine on 11/11/20.
//

#include "../includes/philo_one.h"

int 	print_error(int err)
{
	if (err == 1)
		ft_putstr_fd("Invalid number of arguments\n", 2);
	if (err == 2)
		ft_putstr_fd("Wrong number of philosophers\n", 2);
	if (err == 3)
		ft_putstr_fd("Wrong time of death\n", 2);
	if (err == 4)
		ft_putstr_fd("Wrong meal time\n", 2);
	if (err == 5)
		ft_putstr_fd("Wrong sleep time\n", 2);
	if (err == 6)
		ft_putstr_fd("Malloc error\n", 2);
	if (err == 7)
		ft_putstr_fd("Mutex error\n", 2);
	return (1);
}