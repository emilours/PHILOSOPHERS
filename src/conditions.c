/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:43 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/20 19:19:12 by eminatch         ###   ########.fr       */
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
		ft_error(ERROR_DIGIT);
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
		ft_error(ERROR_DIGIT);
		return (false);
	}
	if (check_values(table) == false)
		return (false);
	return (true);
}

bool	check_values(t_table *table)
{
	if (table->nb_philo <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0
		|| (table->nb_meal <= 0 && table->nb_meal != -1))
	{
		ft_error(ERROR_ZERO);
		return (false);
	}
	if (table->nb_philo > INT_MAX || table->time_to_eat > INT_MAX
		|| table->time_to_die > INT_MAX || table->time_to_sleep > INT_MAX
		|| table->nb_meal > INT_MAX)
	{
		ft_error(ERROR_MAX);
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

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_keeper);
	pthread_mutex_lock(&philo->right_fork);
	ft_write_msg(philo, FORK);
	usleep(philo->table->time_to_die * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->table->time_keeper);
	return (NULL);
}
