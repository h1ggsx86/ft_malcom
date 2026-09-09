/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:23:24 by arotondo          #+#    #+#             */
/*   Updated: 2024/09/15 19:11:35 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	x;
	size_t	y;

	if (!str || !to_find)
		return (NULL);
	x = 0;
	if (*to_find == '\0')
		return ((char *)(str));
	while (str[x] && x < size)
	{
		y = 0;
		while (to_find[y] && str[x + y] == to_find[y] && (x + y) < size)
		{
			if (to_find[y + 1] == '\0')
				return ((char *)(str + x));
			y++;
		}
		x++;
	}
	return (NULL);
}

// char	*ft_strnstr(const char *str, const char *to_find, size_t size)
// {
// 	unsigned int pos;
// 	unsigned int i;

// 	if (!*to_find)
// 		return ((char*)str);
// 	pos = 0;
// 	while (str[pos] != '\0' && (size_t)pos < size)
// 	{
// 		if (str[pos] == to_find[0])
// 		{
// 			i = 1;
// 			while (to_find[i] != '\0' && str[pos + i] == to_find[i] &&
// 					(size_t)(pos + i) < size)
// 				++i;
// 			if (to_find[i] == '\0')
// 				return ((char*)&str[pos]);
// 		}
// 		++pos;
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	char	test1[5] = "AAAAA";
// 	char	to_find1[5] = "AAAAA";
// 	char	test2[18] = "MZIRIBMZIRIBMZE123";
// 	char	to_find2[9] = "MZIRIBMZE";
// 	char	test4[24] = "Bonjour jz je m'appelle";
// 	char	to_find4[7] = "Bonjour";

// 	printf("test 1 = %s\n", ft_strnstr(test1, to_find1, 5));
// 	printf("test 2 = %s\n", ft_strnstr(test2, to_find2, 9));
// 	printf("test 3 = %s\n", ft_strnstr(test3, to_find3, 5));
// 	printf("test 4 = %s\n", ft_strnstr(test4, to_find4, 8));
// 	return (0);
// }
// int	main(int ac, char **av)
// {
// 	if (ac != 4)
// 		return (-1);
// 	else
// 		printf("test : %s\n", ft_strnstr(av[1], av[2], atoi(av[3])));
// 	return (0);
// }