/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:04:40 by arotondo          #+#    #+#             */
/*   Updated: 2024/10/09 19:03:39 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	total_len;

	if (!nmemb || !size)
		return (NULL);
	total_len = nmemb * size;
	if (nmemb != 0 && total_len / nmemb != size)
		return (NULL);
	tab = malloc(total_len);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, total_len);
	return (tab);
}

/*
int	main(void)
{
	ft_calloc(40, 4);
	//calloc(1, 4);
	//a placer ligne 34 pour test :
	//printf("%d", tab[i]);
	//tab = (void *)malloc(nmemb * sizeof(char));
	return (0);
}*/
