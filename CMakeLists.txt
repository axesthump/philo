cmake_minimum_required(VERSION 3.17)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo
        main.c
        includes/philo_one.h
        src/validate.c
        src/print_error.c
        src/ft_atoi.c
        src/init.c
        src/life_simulation.c
        src/ft_isdigit.c
        src/ft_putstr_fd.c
        src/ft_putchar_fd.c
        src/ft_strlen.c
        src/ft_strlcat.c
        src/ft_strlcpy.c
        src/ft_strjoin.c
        src/ft_itoa.c)