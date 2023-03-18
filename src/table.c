/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:50:23 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 20:09:06 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* To create and init new philo and t_philo values*/
t_philo	*ft_init_philo(t_table *table)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->table = table;
	new->dead = false;
	new->last_meal = get_time();
	new->id = 1;
	return (new);
}

/* To create new element in philo list, add it at the end and link it
to the prev philo */
void	philo_list(t_philo *philo, int id)
{
	philo->next = malloc(sizeof(t_philo));
	if (!philo->next)
		return ;
	philo->next->prev = philo;
	philo->next->next = NULL;
	philo->next->table = philo->table;
	philo->next->dead = false;
	philo->next->eat_count = 0;
	philo->next->id = id;
	philo->next->last_meal = get_time();
}

/* To a philo list from a nb of philos, looping with ids, and define
prev, next, start and end as nodes from the list*/
bool	fill_table_list(t_table *table)
{
	t_philo	*temp;
	t_philo	*end;
	int		id;

	id = 2;
	if (table->nb_philo <= 1)
		return (false);
	table->start = ft_init_philo(table);
	if (!table->start)
		return (false);
	temp = table->start;
	while (id <= table->nb_philo)
	{
		philo_list(temp, id);
		if (!temp->next)
			return (false);
		temp = temp->next;
		id++;
	}
	end = temp;
	temp->next = table->start;
	table->start->prev = end;
	return (true);
}

/* Initializes the forks of each philo using locking
mutexes to avoid synchronization conflicts during fork acquisition.
It loops through the list of philo twice, first initializing
each philo's right_fork mutex, then initializing each
philo's left_fork pointer to the right fork mutex of the next philo.
A time_keeper mutex is initialized to synchronize the timing of the philo.*/
bool	init_fork(t_table *table)
{
	t_philo	*start;

	start = NULL;
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		if (pthread_mutex_init(&table->start->right_fork, NULL) != 0)
			return (false);
		table->start = table->start->next;
	}
	start = NULL;
	while (table->start != start)
	{
		if (start == NULL)
			start = table->start;
		table->start->left_fork = &table->start->next->right_fork;
		table->start = table->start->next;
	}
	if (pthread_mutex_init(&table->time_keeper, NULL) != 0)
		return (false);
	return (true);
}
