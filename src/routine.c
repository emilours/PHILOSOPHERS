/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:13:05 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:39:26 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	today_is_ms(int time_ms)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	time_ms = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	if (!time_ms)
		return (ERROR_TIME_MS, 0);
	return (time_ms);
}

bool	philosophers_start_routine(t_table *table)
{
	t_philo	*start;

	start = NULL;
	pthread_mutex_lock(table->time_keeper);
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
	today_is_ms(table->time_ms);
	pthread_mutex_unlock(table->time_keeper);
	if (table->philo->id % 2 == 0)
		usleep(table->philo->table->time_to_eat * 1000); /*attend que les pairs finissent leur premier repas*/
	return (true);
}

void	philosophers_end_routine(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo->id, NULL);
		i++;
	}
	if (table->nb_philo > 1)
		pthread_join(table->monitor, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(table->philo->right_fork);
		i++;
	}
	// pthread_mutex_destroy(table->philo->left_fork);
	pthread_mutex_destroy(table->time_keeper);
	ft_free_philo(table);
}

void	*philosophers_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_write_msg(FORK);
		pthread_mutex_lock(philo->left_fork);
		ft_write_msg(FORK);
		ft_write_msg(EAT);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_write_msg(SLEEP);
		usleep(philo->table->time_to_sleep * 1000);
		ft_write_msg(THINK);
		if (philo->table->nb_philo % 2 == 1) // si nb impair de philo, sleep 20 ms, sinon 0.5 ms
			usleep(200 * 1000);
		else
			usleep(500);
	}
	return (NULL);
}
