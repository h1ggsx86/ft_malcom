/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:52:24 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/22 15:11:57 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*conv_s1;
	const unsigned char	*conv_s2;

	conv_s1 = (unsigned char *)s1;
	conv_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*conv_s1 != *conv_s2)
			return (*conv_s1 - *conv_s2);
		conv_s1++;
		conv_s2++;
		n--;
	}
	return (0);
}
