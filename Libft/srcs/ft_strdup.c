/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:12:03 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 11:54:33 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* retourne un pointeur vers copie d'une chaine de char s
 * en allouant dynamiquement la memoire
 * calcul longueur de la chaine
 * allocation dup = (len + 1) x 1 byte via malloc
 * si la len est null, lalloc est null donc dup est nul et on retourne null
 * copie char by char de s vers dup
 * ajout du caractere nul et on retourne dup
 */

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	length;
	char	*dup;

	length = ft_strlen(s);
	dup = malloc((length + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dup[i] = s[i];
		i++;
	}
	dup[length] = '\0';
	return (dup);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	*dup;

	if (argc != 2)
	{
		printf("usage : <stringtoduplicate>\n");
		return (1);
	}
	
	dup = ft_strdup(argv[1]);
	if (!dup)
	{
		printf("memory allocation failed\n");
		return (1);
	}
	printf("OG String : \"%s\"\n", argv[1]);
	printf("New String : \"%s\"\n", dup);
	free(dup);
	return (0);
}
*/
