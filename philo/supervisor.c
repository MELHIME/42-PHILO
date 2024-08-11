/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:04:33 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/28 10:06:32 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_times(t_philo *philo, int x)
{
	pthread_mutex_lock(&philo->eat_n_mtx);
	if (x == 1)
		philo->eat_n--;
	else
	{
		if (philo->eat_n == 0)
		{
			philo->eat_n = -1;
			pthread_mutex_unlock(&philo->eat_n_mtx);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->eat_n_mtx);
	return (0);
}

void	all_eat_n(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->dead = -1;
	pthread_mutex_unlock(&data->lock);
}

void	after_death(t_data *data, int id)
{
	pthread_mutex_lock(&data->lock);
	data->dead = -1;
	printf("%ld %d died\n", \
		get_time() - data->tm_start, data->philos[id].id);
	pthread_mutex_unlock(&data->lock);
}

void	monitor(t_data *data)
{
	int	id;

	while (1)
	{
		id = 0;
		while (id < data->ttl_ph)
		{
			if (data->n_to_eat)
			{
				if (check_n_times(&data->philos[id], 0) == -1)
				{
					data->cntr++;
					if (data->cntr >= data->ttl_ph)
						return (all_eat_n(data));
				}
			}
			if (get_time() - last_meal(&data->philos[id], 0) >= data->tm_d)
				return (after_death(data, id));
			id++;
		}
		usleep(500);
	}
}
