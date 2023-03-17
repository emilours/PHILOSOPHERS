/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:43 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:50:01 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*fill_table(int ac, char **av, t_philo *philo)
{
	int		flag;

	flag = 0;
	while (av)
	{
		philo->table->nb_philo = ft_atoi_philo(av[1], &flag);
		philo->table->time_to_die = ft_atoi_philo(av[2], &flag);
		philo->table->time_to_eat = ft_atoi_philo(av[3], &flag);
		philo->table->time_to_sleep = ft_atoi_philo(av[4], &flag);
		philo->eat_count = -1;
		if (ac - 1 == 5)
			philo->eat_count = ft_atoi_philo(av[5], &flag);
		if (flag != 0 || ft_check_conditions(av) == false)
		{
			ft_error(ERROR_AV_DIGIT);
			break ;
		}
		else if (philo->table->nb_philo == 0)
		{
			ft_error(ERROR_NO_PHILO);
			break ;
		}
		
	}
	return (philo);
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
