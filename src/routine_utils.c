/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:50:45 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 20:14:01 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Joins all the th created for the philos, ensuring that all th have finished
executing before the program terminates. The linked list traverses through all
the th and joins them one by one.*/
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

/* Checks if a philo has died, based on the current time and time to die.
If the philo has died, it prints a message and kills all philos, returning
true. Otherwise, it returns false */
bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_keeper);
	if ((get_time() - philo->last_meal) > philo->table->time_to_die || philo->dead == true)
	{
		philo->dead = true;
		printf("%ld %d is dead\n", (get_time() - philo->table->time), philo->id);
		// printf("%d", philo->id);
		// printf("is dead");
		kill_philos(philo->table);
		pthread_mutex_unlock(&philo->table->time_keeper);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->time_keeper);
	return (false);
}

/* Sets the dead flag to true for all philos in the table, indicating
that they should stop their routine and iterates over the linked list
of philos and updates their dead flag.*/
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

/* Checks whether all the philos have eaten the required nb of meals, locks
the time_keeper mutex to prevent concurrent access and loops through the list
of philos to count the nb of meals eaten. If a philo has not eaten the
required nb of meals, it returns false. Otherwise it returns true,
prints the total nb of meals, and kills_philos to end the simulation */
bool	check_meals(t_philo *philo)
{
	t_philo	*start;

	start = NULL;
	if (philo->table->nb_meal == -1)
		return (false);
	pthread_mutex_lock(&philo->table->time_keeper);
	while (philo != start)
	{
		if (start == NULL)
			start = philo;
		if (philo->eat_count < philo->table->nb_meal)
		{
			pthread_mutex_unlock(&philo->table->time_keeper);
			return (false);
		}
		philo = philo->next;
	}
	printf("%d", philo->eat_count);
	ft_error(EAT_COUNT); // utilise printf
	kill_philos(philo->table);
	pthread_mutex_unlock(&philo->table->time_keeper);
	return (true);
}

/* Monitor the state of the dining philos and checks if any philo has died
or if all philos have eaten the required nb of meals, and ends the program
if any of these conditions are met */
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
