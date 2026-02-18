/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:23 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 13:09:34 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	memmove qui ne gere pas les chevauchement */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <src> <destsize> <sizen>");
		return (1);
	}

	const char	*src;
	char		*dest;
	int		dest_size;
	size_t		n;
	src = argv[1];
	dest_size = atoi(argv[2]);
	n = atoi(argv[3]);
	if (dest_size <= 0)
	{
		printf("error, dest size must be > 0\n");
		return (1);
	}
	dest = calloc(dest_size, sizeof(char));
	if (!dest)
	{
		printf("calloc error");
		return (1);
	}
	ft_memcpy(dest, src, n);
	printf("ft_memcpy result : \"%s\"\n", dest);
	free(dest);
	return (0);
}
*/		
