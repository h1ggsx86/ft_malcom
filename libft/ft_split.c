/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <tnedel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:59:20 by arotondo          #+#    #+#             */
/*   Updated: 2026/07/06 18:50:11 by tnedel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char sep)
{
	size_t	x;
	size_t	nb;

	x = 0;
	nb = 0;
	if (!str)
		return (0);
	while (str[x] != '\0')
	{
		if (str[x] != sep && (str[x + 1] == sep || str[x + 1] == '\0'))
			nb++;
		x++;
	}
	return (nb);
}

static void	*ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word;
	char	**tab;

	tab = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	word = 0;
	while (word < count_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		tab[word] = (char *)ft_calloc((i - j + 1), sizeof(char));
		if (!tab[word])
			return (ft_free(tab));
		ft_strlcpy(tab[word], (s + j), (i - j + 1));
		word++;
	}
	return (tab);
}

// int	main(int argc, char **argv)
// {
// 	char	**ret;
// 	int		i;

// 	if (argc != 3)
// 		return (0);
// 	else
// 	{
// 		ret = ft_split(argv[1], *argv[2]);
// 		i = 0;
// 		while (ret[i])
// 		{
// 			printf("%s\n", ret[i]);
// 			free (ret[i]);
// 			i++;
// 		}
// 		free (ret);
// 		return (1);
// 	}
// }