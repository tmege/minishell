/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:43:02 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 11:55:37 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* retourne une nouv chaine contenant s1 sans les char 
 * presents dans set en debut et fin de chaine
 * renvoie 1 si c est dans set sinon 0
 * utilisee pour tester si le char est a supprimer
 */

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

/* verifie si set et s1 ne sont pas nuls, sinon retourne null
 * supprime les caracteres du debut de chaine avec start
 * supprime les caracteres de fin de chaine avec end
 * calcul la longueur de la nouvelle chaine end - start
 * alloue dynamiquement end - start + 1 byte
 * verifie si l'allocation a bien fonctionnee
 * copie len (end -start) char depuis s1[start] avec ft_memcpy
 * ajoute le caractere nul final
 */

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_in_set(s1[end - 1], set))
		end--;
	len = end - start;
	trim = (char *)malloc(len + 1);
	if (!trim)
		return (NULL);
	ft_memcpy(trim, &s1[start], len);
	trim[len] = '\0';
	return (trim);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : ./exec <string> <set>\n");
		return (1);
	}
	const char	*s1;
	const char	*set;
	char		*result;

	s1 = argv[1];
	set = argv[2];
	result = ft_strtrim(s1, set);
	if (result)
	{
		printf("result : '%s'\n", result);
		free(result);
	}
	else
		printf("error, function returned null");
	return (0);
}
*/
