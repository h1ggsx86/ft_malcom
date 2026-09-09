/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:13:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/20 19:52:21 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	long	signe;
	long	value;

	i = 0;
	signe = 0;
	value = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			signe++;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		value *= 10;
		value += str[i] - 48;
		i++;
	}
	if (signe % 2 == 1)
		value *= -1;
	return (value);
}
