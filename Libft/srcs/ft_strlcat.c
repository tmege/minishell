/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:51:32 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 11:48:01 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* concatene src a la fin de dest selon la size max du buffer de dest
 * calcul len de src et len de dest
 * si la size est inferieur a dest actuelle on a pas la place 
 * donc on retourne size+ len src pour afficher la longueur theorique necessaire
 * copie des char de src 1 by 1 a la suite de dest tant que dest < size - 1
 * termine la chaine par caractere nul
 * retour len totale et si len total < size alors la concatenation est tronquee
 * permet au programme appelant de savoir si c'est tronque
 */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (dest[dest_len])
		dest_len++;
	while (src[src_len])
		src_len++;
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
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

	char	buffer[100];
	size_t	result;
	size_t	n;

	n = atoi(argv[3]);
	ft_strlcpy(buffer, argv[1], sizeof(buffer));
	result = ft_strlcat(buffer, argv[2], n);

	printf("Result : %zu\n", result);
	printf("Final string : '%s'\n", buffer);
}
*/
