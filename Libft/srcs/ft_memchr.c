/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:42:37 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:06:24 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* recherche premiere occurence d'un char dans une portion de memoire
 * lecture byte par byte en comparant au char
 * si trouve retourne pointeur vers ce byte
 * si pas trouve retourne NULL
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)((const unsigned char *)s + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <str> <char> <sizen>\n");
		return (1);
	}
	
	const char	*str;
	int		c;
	size_t		n;
	void		*result;

	str = argv[1];
	c = (unsigned char)argv[2][0];
	n = (size_t)atoi(argv[3]);
	result = ft_memchr(str, c, n);
	if (result)
		printf("ft_memchr found %c at position %ld\n", c, (char *)result - str);
	else 
		printf("%c not found in the first %zu bytes\n", c, n);
	return (0);
}
*/
