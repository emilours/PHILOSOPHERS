/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:29:32 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/19 19:36:35 by eminatch         ###   ########.fr       */
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

/* tests ultimes : 200 410 200 200 + regarder discord + testeurs && si av <= 0 +
clean liste chainee fill table list && init fork + message eat count + norme */

/* CORRECTION OREN
	ft_usleep 100ms apres time_to_die > died et boucle infinie
	1 mutex pour ecrire, pour manger, un pour heure, um pour dead... > possible solution pour deadlocks
	conditions speciale pour 1 philo : il meurt usleep apres avoir pris sa premiere fourchette + afficher message mort > data race
	*/
