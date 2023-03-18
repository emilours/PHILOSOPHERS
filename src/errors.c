/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:51 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 19:20:15 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *s)
{
	printf(ERROR_MSG);
	printf("%s", s);
}

/* Frees the memory allocated to the linked list of t_philo structures,
iterates through the list and frees each node until it reaches the
original starting node */
void	ft_free_philo(t_table *table)
{
	t_philo	*start;
	t_philo	*tmp;

	if (!table->start)
		return ;
	start = table->start;
	tmp = NULL;
	if (table->start->next == start)
	{	
		free(table->start);
		table->start = NULL;
		return ;
	}
	table->start = table->start->next;
	while (tmp != start)
	{
		tmp = table->start->next;
		free(table->start);
		table->start = tmp;
	}
	free(table->start);
	table->start = NULL;
}

void	ft_write_msg(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->table->time_keeper);
	if (philo->dead == false)
		printf("%ld %d %s", (get_time() - philo->table->time), philo->id, s);
	pthread_mutex_unlock(&philo->table->time_keeper);
}
