/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:29:32 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/20 20:38:46 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_philo_and_forks(t_table *table)
{
	if (fill_table_list(table) == false)
	{
		ft_error(ERROR_PHILO);
		ft_free_philo(table);
		return (false);
	}
	if (init_fork(table) == false)
	{
		ft_error(ERROR_MUTEX);
		ft_free_philo(table);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac > 6 || ac < 5)
	{
		ft_error(ERROR_AC);
		return (1);
	}
	if (check_table(ac, av, &table) == false)
		return (1);
	if (check_philo_and_forks(&table) == false)
		return (1);
	philosophers_start_routine(&table);
	philosophers_end_routine(&table);
	ft_free_philo(&table);
	return (0);
}

/* condition pour un philo qui foire */
