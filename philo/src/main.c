/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:28:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/15 13:48:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
TODO:
Check for leaks
Check for mutex destruction
./philo 4 2147483647 200 200 seg faults (???)

All tests:
./philo
./philo 1
./philo 1 2
./philo 1 2 3	Invalid argument / usage message.
./philo 4 500 abc 200	Invalid argument.
./philo 4 500 200 2.9	Invalid argument.
./philo 4 -500 200 200	Invalid argument.
./philo 4 2147483648 200 200	Invalid argument.
./philo 0 800 200 200	Invalid argument.
./philo 500 100 200 200	2 defensible solutions:
– Invalid argument. (ex. Max 200 philosophers)
– A philosopher dies at 100 ms.
./philo 4 2147483647 200 200	No one dies.
./philo 4 200 2147483647 200	A philosopher dies at 200 ms.
./philo 4 800 200 2147483647	A philosopher dies at 800 ms.
./philo 2 800 200 200	No one dies.
./philo 5 800 200 200	No one dies.
./philo 5 0 200 200	A philosopher dies at 0 ms.
./philo 5 800 0 200	No one dies.
./philo 5 800 200 0	No one dies.
./philo 5 800 0 0	No one dies.
./philo 5 800 200 200 0	2 defensible solutions:
– Invalid argument.
– Simulation stops immediately because everyone ate 0 times.
./philo 4 410 200 200	No one dies.
./philo 1 200 200 200	Philosopher 1 takes a fork and dies at 200 ms.
./philo 4 2147483647 0 0	No one dies.
./philo 4 200 210 200	A philosopher dies at 200 ms.
./philo 2 600 200 800	A philosopher dies at 600 ms.
./philo 4 310 200 200	A philosopher dies at 310 ms.
./philo 3 400 100 100 3	No one dies, each philosopher eats at least 3 times.
./philo 200 800 200 200 9	No one dies, each philosopher eats at least 9 times.
./philo 200 410 200 200	A philosopher dies at 410 ms.


Failed tests:
./philo 4 200 2147483647 200
	Expected output: A philosopher dies at 200 ms.

*/

void leaks()
{
	system ("leaks -q philo");
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	// atexit(leaks);
	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of arguments\n"));
	if (ft_are_args_valid(av))
		return (printf("Error: invalid argument(s)\n"));
	ft_initialization(&data, av);
	ft_annihilation(data);
}
