/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:50:45 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:15:41 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	join_threads(t_table *table)
{
	t_philo	*start;

	start = NULL;
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		pthread_join(table->start->th, NULL);
		table->start = table->start->next;
	}
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->table->time_keeper);
	today_is_ms(philo->table->time_ms);
	if (philo->table->time_ms >= philo->time_to_die
		|| philo->dead == true)
	{
		philo->dead = true;
		printf("%d", philo->id);
		ft_write_msg(DEATH);
		printf("%d", philo->table->time_ms);
		kill_philos(philo->table);
		pthread_mutex_unlock(philo->table->time_keeper);
		return (true);
	}
	pthread_mutex_unlock(philo->table->time_keeper);
	return (false);
}

void	kill_philos(t_table *table)
{
	t_philo	*start;

	start = NULL;
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		table->start->dead = true;
		table->start = table->start->next;
	}
}

bool	check_meals(t_philo *philo)
{
	t_philo	*start;

	start = NULL;
	pthread_mutex_lock(philo->table->time_keeper);
	while (philo != start)
	{
		if (start == NULL)
			start = philo;
		if (philo->eat_count < philo->table->nb_meal)
		{
			pthread_mutex_unlock(philo->table->time_keeper);
			return (false);
		}
		philo = philo->next;
	}
	printf("%d", philo->eat_count);
	ft_write_msg(EAT_COUNT);
	kill_philos(philo->table);
	pthread_mutex_unlock(philo->table->time_keeper);
	return (true);
}

void	*ft_monitoring(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	while (1)
	{
		usleep(500);
		if (is_dead(table->start) == true)
			break ;
		if (check_meals(table->start) == true)
			break ;
		table->start = table->start->next;
	}
	join_threads(table);
	return (NULL);
}
