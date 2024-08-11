/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:19:59 by mel-hime          #+#    #+#             */
/*   Updated: 2024/06/29 12:28:33 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tm_now;

	if (gettimeofday(&tm_now, NULL))
		return (-1);
	return (tm_now.tv_sec * 1000 + tm_now.tv_usec / 1000);
}

void	message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead != -1)
		printf("%ld %d %s\n", \
			get_time() - philo->data->tm_start, philo->id, msg);
	pthread_mutex_unlock(&philo->data->lock);
}

void	eat_sleep(int time, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(70);
		if (is_dead(philo) == -1)
			return ;
	}
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead == -1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	ft_atoi(char *str)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (str == NULL || str[i] == '-' || str[i] == '\0')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - 48;
		i++;
		if (number > 2147483647 || number < -2147483648)
			return (-1);
	}
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (str[i] != '\0' || number == 0)
		return (-1);
	return (number);
}
