/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:29:32 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 21:26:30 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac > 6 || ac < 5)
	{
		ft_error(ERROR_AC);
		return (1);
	}
	if (check_table(ac, av, &table) == false)
	{
		ft_error(ERROR_NO_PHILO);
		return (1);
	}
	if (fill_table_list(&table) == false)
	{
		ft_error(ERROR_NO_PHILO);
		return (1);
	}
	if (init_fork(&table) == false)
	{
		ft_error(ERROR_MUTEX);
		return (1);
	}
	philosophers_start_routine(&table);
	philosophers_end_routine(&table);
	ft_free_philo(&table);
	return (0);
}


/* tests ultimes : 200 410 200 200 + regarder discord + testeurs && si av <= 0 + died au lieu de is dead + retirer maj milieu de phrase
clean liste chainee fill table list && init fork */