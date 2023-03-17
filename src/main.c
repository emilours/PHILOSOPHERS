/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:29:32 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:37:27 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac > 6 || ac < 5)
		ft_error(ERROR_AC);
	fill_table(ac, av, table->philo);
	philosophers_start_routine(table);
	philosophers_end_routine(table);
	ft_free_philo(table);
	return (0);
}