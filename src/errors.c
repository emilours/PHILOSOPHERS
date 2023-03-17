/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:51 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:38:50 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *s)
{
	printf(ERROR_MSG);
	printf("%s", s);
}

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

char	**ft_free(char **str)
{	
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
