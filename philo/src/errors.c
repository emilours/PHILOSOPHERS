/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:51 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/21 17:50:19 by eminatch         ###   ########.fr       */
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

void	ft_print_status(t_philo *philo, char *c, char *str)
{
	pthread_mutex_lock(&philo->table->time_keeper);
	pthread_mutex_lock(&philo->table->print_keeper);
	if (philo->dead == false)
		printf("%s%ld %d %s%s", c, (get_time() - philo->table->time), philo->id,
			str, RESET);
	pthread_mutex_unlock(&philo->table->print_keeper);
	pthread_mutex_unlock(&philo->table->time_keeper);
}

void	ft_write_msg(t_philo *philo, t_status status)
{
	if (status == EATING)
		ft_print_status(philo, GREEN, "is eating\n");
	else if (status == SLEEPING)
		ft_print_status(philo, BLUE, "is sleeping\n");
	else if (status == THINKING)
		ft_print_status(philo, PINK, "is thinking\n");
	else if (status == FORK)
		ft_print_status(philo, YELLOW, "has taken a fork\n");
}

/* Returns the current time in milliseconds. Gettimeofday gets the current
time and calculates it in milliseconds */
long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
