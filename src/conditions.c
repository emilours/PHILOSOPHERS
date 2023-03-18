/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:43 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/18 17:29:50 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Fills in the attributes with av and returns true if success */
bool	check_table(int ac, char **av, t_table *table)
{
	int	flag;

	flag = 0;
	if (ft_check_conditions(av) == false)
	{
		ft_error(ERROR_AV_DIGIT);
		return (false);
	}
	table->nb_philo = ft_atoi_philo(av[1], &flag);
	table->time_to_die = ft_atoi_philo(av[2], &flag);
	table->time_to_eat = ft_atoi_philo(av[3], &flag);
	table->time_to_sleep = ft_atoi_philo(av[4], &flag);
	if (ac - 1 == 5)
		table->nb_meal = ft_atoi_philo(av[5], &flag);
	else
		table->nb_meal = -1;
	if (flag != 0)
	{
		ft_error(ERROR_AV_DIGIT);
		return (false);
	}
	else if (table->nb_philo == 0)
	{
		ft_error(ERROR_NO_PHILO);
		return (false);
	}
	return (true);
}

int	ft_atoi_philo(const char *s, int *flag)
{
	int	j;
	int	nb;

	if (s == NULL)
		return (++*flag, 0);
	j = 1;
	nb = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			j = -j;
		s++;
	}
	if (*s < '0' || *s > '9')
		return (++*flag, 0);
	ft_atoi_philo_bis(s, flag, &j, &nb);
	return (nb * j);
}

void	ft_atoi_philo_bis(const char *s, int *flag, int *j, int *nb)
{
	while (*s >= '0' && *s <= '9')
	{
		if (*j > 0 && (INT_MAX - *s + '0') / 10 < *nb)
		{
			++*flag;
			break ;
		}
		if (*j < 0 && (INT_MIN + *s - '0') / 10 > -*nb)
		{
			++*flag;
			break ;
		}
		*nb = *nb * 10 + *s - '0';
		s++;
	}
}
