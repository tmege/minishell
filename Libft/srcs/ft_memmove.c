/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:40:11 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 13:50:06 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	verifie si les pointeurs ne sont pas null
*	conversion en unsigned char pour travailler byte par byte
*	si dest est apres src, il y a risque de chevauchement donc on priorise..
* la copie en partant de la fin pour eviter d'ecraser des donnes pas encore lues
*	sinon copie normale de gauche a droite
*	retour du pointeur destination
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <src> <destsize> <sizen>\n");
		return (1);
	}

	const char	*src;
	int		dest;
	size_t		n;
	char		*buf;

	src = argv[1];
	dest = atoi(argv[2]);
	n = atoi(argv[3]);
	if (dest < 0 || (size_t)dest > ft_strlen(src))
	{
		printf("error, invalid dest size\n");
		return (1);
	}
	buf = ft_strdup(src);
	if (!buf)
	{
		printf("error ft_strdup\n");
		return (1);
	}
	printf("OG string : \"%s\"\n", src);
	ft_memmove(buf + dest, buf, n);
	printf("After memmove string : \"%s\"\n", buf);
	return (0);
}
*/
