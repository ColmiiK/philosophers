/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:38:21 by alvega-g          #+#    #+#             */
/*   Updated: 2024/02/16 16:49:28 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_edge_case_fork(t_data *data, int i)
{
	if (data->philo[i].r_fork == data->philo[i].l_fork)
	{
		ft_flag_change(data);
		printf(FORK_MSG, (size_t)2, 0);
		ft_usleep(data->philo[i].die_ms);
		printf(DEAD_MSG, data->philo[i].die_ms, 0);
		return (1);
	}
	return (0);
}

int	ft_edge_case_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->dead_lock);
		ft_usleep(2);
		ft_printf_alive(&data->philo[i], 'd');
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

static int	ft_edge_cases(t_data *data)
{
	if (data->philo[0].die_ms == 0)
	{
		printf(DEAD_MSG, (size_t)0, data->philo[0].id);
		return (1);
	}
	return (0);
}

static int	ft_threads(t_data *data, int n_of_philos)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	if (ft_edge_cases(data))
		return (0);
	while (++i < n_of_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				&ft_philos, &data->philo[i]))
		{
			data->dead = true;
			break ;
		}
	}
	if (pthread_create(&monitor, NULL, &ft_monitor, data))
		data->dead = true;
	if (pthread_join(monitor, NULL))
		return (1);
	while (--i >= 0)
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	return (0);
}

int	ft_initialization(t_data **data, char **av)
{
	pthread_mutex_t	*forks;
	int				i;

	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (printf("Error: unable to malloc (data)\n"));
	if (ft_setup_struct(*data, av))
		return (printf("Error: unable to setup data\n"));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atol(av[2]));
	if (ft_setup_mutex(*data, (*data)->n_of_philos, forks))
	{
		free(forks);
		return (printf("Error: unable to initialize mutexes\n"));
	}
	if (ft_threads(*data, (*data)->n_of_philos))
	{
		free(forks);
		return (printf("Error: unable to create threads\n"));
	}
	i = -1;
	while (++i < (*data)->n_of_philos)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	return (0);
}
