/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:20:10 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/07 19:15:29 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	value;

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
