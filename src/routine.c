/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:13:05 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 20:13:24 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Returns the current time in milliseconds. Gettimeofday gets the current
time and calculates it in milliseconds */
long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* Creates threads for philo and a monitor, updates the current time,
waits 20 ms for even philos to eat and uses mutexes to synchronize
access to shared resources */
bool	philosophers_start_routine(t_table *table)
{
	t_philo	*start;

	start = NULL;
	pthread_mutex_lock(&table->time_keeper);
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		if (pthread_create(&table->start->th, NULL,
				&philosophers_routine, table->start) != 0)
			return (false);
		table->start = table->start->next;
	}
	if (pthread_create(&table->monitor, NULL, &ft_monitoring, table) != 0)
		return (false);
	table->time = get_time(); /* heure de depart */
	pthread_mutex_unlock(&table->time_keeper);
	return (true);
}

/* waits for all philo threads to finish, destroys right forks mutexes,
destroys time_keeper mutex, and frees memory allocated to philo structure */
void	philosophers_end_routine(t_table *table)
{
	t_philo	*start;

	start = NULL;
	if (table->nb_philo > 1)
		pthread_join(table->monitor, NULL);
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		pthread_mutex_destroy(&table->start->right_fork);
		table->start = table->start->next;
	}
	pthread_mutex_destroy(&table->time_keeper);
}

/* Entry point for philo threads. Uses mutex locks to allow each philo
to take forks and eat in turn. After each meal, the philo sleeps for a
certain amount of time, then spends time thinking before starting the
cycle again. If the number of philo is odd, each philo sleeps for 20 ms
between each cycle, otherwise they sleep for only 0.5 ms.*/
void	*philosophers_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->table->time_keeper);
		if (philo->dead == true)
		{
			pthread_mutex_unlock(&philo->table->time_keeper);
			break ;
		}
		pthread_mutex_unlock(&philo->table->time_keeper);
		pthread_mutex_lock(&philo->right_fork);
		ft_write_msg(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		ft_write_msg(philo, FORK);
		ft_write_msg(philo, EAT);
		pthread_mutex_lock(&philo->table->time_keeper);
		philo->last_meal = get_time();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->table->time_keeper);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		ft_write_msg(philo, SLEEP);
		usleep(philo->table->time_to_sleep * 1000);
		ft_write_msg(philo, THINK);
		if (philo->table->nb_philo % 2 == 1)
			usleep(200 * 1000);
		else
			usleep(500);
	}
	return (NULL);
}
