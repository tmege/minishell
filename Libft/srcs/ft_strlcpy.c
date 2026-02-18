/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:48:46 by tmege             #+#    #+#             */
/*   Updated: 2025/04/30 14:47:14 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copier src dans dest sans depasser size -1
 * retourne len total src meme si size = 0
 * si le buffer de dest est nul on copie rien et retourne 0
 * copie char by char jusqua size -1
 * ajoute caractere nul
 * calcul et retourne la len totale 
 */

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <src> <dest> <size>\n");
		return (1);
	}

	const char	*src;
	const char	*dest_init;
	size_t		size;
	size_t		result;
	char		dest[100];

	src = argv[1];
	dest_init = argv[2];
	size = atoi(argv[3]);

	ft_strlcpy(dest, dest_init, sizeof(dest));

	result = ft_strlcpy(dest, src, size);

	printf("Result : %zu\n", result);
	printf("Final string in dest : '%s'\n", dest);
	return (0);
}
*/
