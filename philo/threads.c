/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:02:42 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/24 17:45:09 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_dead(philo) == 0)
	{
		if (philo->state == gosleep)
			go_sleep(philo);
		else
			go_eat(philo);
	}
	return (NULL);
}

int	join_th(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->ttl_ph)
	{
		if (pthread_join(threads[i++], NULL))
		{
			free(threads);
			return (-1);
		}
	}
	free(threads);
	return (0);
}

int	create_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(data->ttl_ph * sizeof(pthread_t));
	if (!threads)
		return (-1);
	data->tm_start = get_time();
	while (i < data->ttl_ph)
	{
		last_meal(&data->philos[i], 1);
		if (pthread_create(&threads[i], NULL, routine, &data->philos[i]))
		{
			free(threads);
			return (-1);
		}
		i++;
	}
	monitor(data);
	if (join_th(data, threads))
		return (0);
	return (0);
}
