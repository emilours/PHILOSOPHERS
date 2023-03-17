/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:43:31 by eminatch          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:14 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_nb(char *av)
{
	int	i;

	i = 0;
	if (is_sign(av[i]) == true && av[i + 1] != '\0')
		i++;
	while (av[i] && is_digit(av[i]) == true)
		i++;
	if (av[i] != '\0' && is_digit(av[i]) == false)
		return (false);
	return (true);
}

bool	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_check_conditions(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_nb(av[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
