/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:23:54 by arotondo          #+#    #+#             */
/*   Updated: 2024/10/02 14:17:22 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strcat(char *dest, char *src)
// {
// 	int	i;
// 	int	destlen;

// 	destlen = ft_strlen(dest);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[destlen + i] = src[i];
// 		i++;
// 	}
// 	dest[destlen + i] = '\0';
// 	return (dest);
// }

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
