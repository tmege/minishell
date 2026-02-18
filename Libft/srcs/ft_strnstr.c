/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:57:11 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:07:51 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* cherche premiere occurence de needle dans haystack sur une len limite
 * retourne pointeur vers le debut de l'occurence de needle dans haystack
 * si needle vide on retourne haystack
 * on boucle dans haystack dans la len limit
 * on compare haystack i+j a needle j pour chaque pos
 * 	 de i en sassurant que i+j < len limit
 * si on atteint la fin de needle c'est quon la
 * 	 entierement retrouve et on retourne le pointeur
 * sinon on continue sur les positions suivante de haystack
 * si on a parcouru len sans trouver needle on retourne null
 */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
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
		printf("usage : ./exec <haystack> <needle> <len>");
		return (1);
	}
	const char 	*haystack;
	const char	*needle;
	size_t		len;
	char		*result;

	haystack = argv[1];
	needle = argv[2];
	len = atoi(argv[3]);
	result = ft_strnstr(haystack, needle, len);
	printf("Result : %s\n", result);
	return (0);
}
*/
