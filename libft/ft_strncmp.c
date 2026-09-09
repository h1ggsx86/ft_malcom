/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:47:47 by arotondo          #+#    #+#             */
/*   Updated: 2024/12/10 16:23:02 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*conv_s1;
	const unsigned char	*conv_s2;

	conv_s1 = (const unsigned char *)s1;
	conv_s2 = (const unsigned char *)s2;
	while (*conv_s1 && *conv_s2 && *conv_s1 == *conv_s2 && n > 0)
	{
		conv_s1++;
		conv_s2++;
		n--;
	}
	if (n == 0 || *conv_s1 == *conv_s2)
		return (0);
	else
		return (*conv_s1 - *conv_s2);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
// 		i++;
// 	return (s1[i] - s2[i]);
// }

/*
int	main(int argc, char **argv)
{
	if (argc != 4)
		return (1);
	printf("%d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
	return (0);
}*/
