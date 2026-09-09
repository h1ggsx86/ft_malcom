/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:29:41 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/22 15:14:54 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	set_in(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	len;
	size_t	start;
	size_t	end;

	start = 0;
	while (set_in((s1[start]), set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && set_in(((char)s1[end]), set))
	{
		end--;
	}
	len = end - start + 1;
	s2 = ft_calloc((len + 1), sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, (s1 + start), len + 1);
	return (s2);
}
