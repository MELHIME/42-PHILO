/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:21:40 by mel-hime          #+#    #+#             */
/*   Updated: 2024/06/30 07:43:28 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	message("has taken a fork", philo);
	if (philo->data->ttl_ph == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		while (is_dead(philo) == 0)
			;
	}
	pthread_mutex_lock(philo->r_fork);
	message("has taken a fork", philo);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->state = gosleep;
}

long	last_meal(t_philo *philo, int x)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meal_mtx);
	if (x == 1)
		philo->lastmeal = get_time();
	else
	{
		last_meal = philo->lastmeal;
		pthread_mutex_unlock(&philo->meal_mtx);
		return (last_meal);
	}
	pthread_mutex_unlock(&philo->meal_mtx);
	return (-1);
}

void	go_sleep(t_philo *philo)
{
	message("is sleeping", philo);
	eat_sleep(philo->data->tm_s, philo);
	philo->state = goeat;
}

void	go_eat(t_philo *philo)
{
	message("is thinking", philo);
	if (is_dead(philo) == -1)
		return ;
	take_forks(philo);
	message("is eating", philo);
	last_meal(philo, 1);
	eat_sleep(philo->data->tm_e, philo);
	if (philo->data->n_to_eat != 0)
		check_n_times(philo, 1);
	put_forks(philo);
}
