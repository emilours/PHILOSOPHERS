/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:43:31 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/21 17:50:15 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

/* Checks whether the string input is a valid nb by checking if it contains
only digits, except for a possibl sign */
bool	is_nb(char *av)
{
	int	i;

	i = 0;
	if (is_sign(av[i]))
		i++;
	while (av[i] && is_digit(av[i]) == true)
		i++;
	if (i != ft_strlen(av))
		return (false);
	return (true);
}

/* checks if a character is a + */
bool	is_sign(char c)
{
	if (c == '+')
		return (true);
	return (false);
}

/* checks if a character is a digit */
bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

/*  checks if all the elements are numbers */
bool	ft_check_conditions(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_nb(av[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
