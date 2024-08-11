/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:23:10 by mel-hime          #+#    #+#             */
/*   Updated: 2024/06/30 09:13:03 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_numbers(t_data *data, int ac, char **av)
{
	data->ttl_ph = ft_atoi(av[1]);
	if (data->ttl_ph == -1)
		return (-1);
	data->tm_d = ft_atoi(av[2]);
	if (data->tm_d == -1)
		return (-1);
	data->tm_e = ft_atoi(av[3]);
	if (data->tm_e == -1)
		return (-1);
	data->tm_s = ft_atoi(av[4]);
	if (data->tm_s == -1)
		return (-1);
	if (ac == 6)
	{
		data->n_to_eat = ft_atoi(av[5]);
		if (data->n_to_eat == -1)
			return (-1);
	}
	else
		data->n_to_eat = 0;
	data->dead = 0;
	data->stop = 1;
	return (0);
}

static int	alloc_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->ttl_ph * sizeof(pthread_mutex_t *));
	if (data->forks == NULL)
		return (-1);
	data->philos = malloc(data->ttl_ph * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	while (i < data->ttl_ph)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (-1);
		if (i % 2 == 0)
			(data->philos[i]).state = goeat;
		else
			(data->philos[i]).state = gosleep;
		i++;
	}
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ttl_ph)
	{
		(data->philos[i]).id = i + 1;
		if (data->n_to_eat == 0)
			(data->philos[i]).eat_n = -1;
		else
			(data->philos[i]).eat_n = data->n_to_eat;
		data->philos[i].lastmeal = get_time();
		if (pthread_mutex_init(&((data->philos[i]).meal_mtx), NULL))
			return (-1);
		if (pthread_mutex_init(&((data->philos[i]).eat_n_mtx), NULL))
			return (-1);
		if (pthread_mutex_init(data->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

static int	give_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->lock, NULL))
		return (-1);
	if (pthread_mutex_init(&data->lock_n_times, NULL))
		return (-1);
	while (i < (data->ttl_ph - 1))
	{
		(data->philos[i]).r_fork = data->forks[i];
		(data->philos[i]).data = data;
		(data->philos[i]).l_fork = data->forks[i + 1];
		i++;
	}
	(data->philos[i]).r_fork = data->forks[i];
	(data->philos[i]).data = data;
	(data->philos[i]).l_fork = data->forks[0];
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	if (get_numbers(data, ac, av) == -1)
	{
		error("\033[1;31mError!!! Invalid Number \n\033[0m");
		return (-1);
	}
	if (alloc_data(data) == -1)
	{
		error("\033[1;31mError!!! Allocation Failed \n\033[0m");
		return (-1);
	}
	if (init_philo(data) == -1)
	{
		error("\033[1;31mError!!! Mutex Failed \n\033[0m");
		return (-1);
	}
	if (give_forks(data) == -1)
	{
		error("\033[1;31mError!!! Mutex Failed \n\033[0m");
		return (-1);
	}
	return (0);
}
