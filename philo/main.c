/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:19:50 by mel-hime          #+#    #+#             */
/*   Updated: 2024/06/29 07:50:11 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(2, &str[i++], 1);
	return ;
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ttl_ph)
	{
		pthread_mutex_destroy(data->forks[i]);
		pthread_mutex_destroy(&(data->philos[i].eat_n_mtx));
		pthread_mutex_destroy(data->philos[i].l_fork);
		pthread_mutex_destroy(data->philos[i].r_fork);
		pthread_mutex_destroy(&(data->philos[i].meal_mtx));
		free(data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(data->lock_n_times));
	pthread_mutex_destroy(&(data->lock));
	free(data->forks);
	free(data->philos);
}

int	main(int ac, char **av)
{
	static t_data	data;

	if (ac < 5 || ac > 6)
	{
		error("\033[1;31mError!!! check ur args \n\033[0m");
		return (-1);
	}
	if (init(&data, ac, av))
		return (-1);
	if (create_threads(&data))
	{
		free_all(&data);
		return (-1);
	}
	free_all(&data);
	return (0);
}
