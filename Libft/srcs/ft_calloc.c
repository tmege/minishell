/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:06:26 by tmege             #+#    #+#             */
/*   Updated: 2025/05/01 17:50:12 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* alloue la memoire et initialize celle ci a zero*/

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(n * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, n * size);
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	int *tab;
	int i;

	tab = ft_calloc(3, sizeof(int));
	if (!tab)
	{
		printf("failed to allocate memory.\n");
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		printf("tab[%d] = %d\n", i, tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
*/
