/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:35 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 12:49:55 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compare deux zones de memoire byte par byte
 * retourne valeur positive si 1>2 ou negative si 1<2
 */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <s1> <s2> <sizen>\n");
		return (1);
	}

	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t			n;
	int			result;
	s1 = argv[1];
	s2 = argv[2];
	n = atoi(argv[3]);
	result = ft_memcmp(s1, s2, n);
	printf("ft_memcmp result is %d\n", result);
	return (0);
}
*/
