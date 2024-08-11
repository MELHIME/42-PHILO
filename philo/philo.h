/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:27:57 by mel-hime          #+#    #+#             */
/*   Updated: 2024/06/30 07:45:48 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef enum s_state
{
	goeat = 1,
	gosleep = 2
}	t_state;

typedef struct s_philo
{
	int				id;
	long			lastmeal;
	long			start;
	int				eat_n;
	t_state			state;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	eat_n_mtx;
	pthread_mutex_t	meal_mtx;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				ttl_ph;
	int				cntr;
	long			tm_start;
	int				tm_d;
	int				tm_s;
	int				tm_e;
	int				n_to_eat;
	int				dead;
	int				stop;
	t_philo			*philos;
	pthread_mutex_t	lock_n_times;
	pthread_mutex_t	**forks;
	pthread_mutex_t	lock;
}	t_data;

long		get_time(void);
void		message(char *msg, t_philo *philo);
int			is_dead(t_philo *philo);
void		eat_sleep(int time, t_philo *philo);
void		error(char *str);
int			ft_atoi(char *str);
int			init(t_data *data, int ac, char **av);
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);
int			check_n_times(t_philo *philo, int x);
long		last_meal(t_philo *philo, int x);
void		go_sleep(t_philo *philo);
void		go_eat(t_philo *philo);
void		*routine(void *arg);
int			join_th(t_data *data, pthread_t *threads);
void		monitor(t_data *data);
int			create_threads(t_data *data);
void		free_all(t_data *data);

#endif