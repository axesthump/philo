#include "includes/philo_one.h"

int		main(int argc, char **argv)
{
	int err;
	t_table table;
	t_args	args;
	int 	i;

	table.args = &args;
	if ((err = validate_and_parse(argv, argc, &args)))
		return (print_error(err));
	if ((err = init_table(&table, &args)))
		return (print_error(err)); //Ошибка маллока
	i = 0;
	while (i < args.num_philo)
	{
		pthread_join(table.philos[i].thread, NULL);
		++i;
	}
	return (0);
}
