/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:16:03 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:01:25 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* cree une nouv chaine s en appliquant une fonction f 
 * 	a chaque char de celle ci sans modif l'originale
 * verifie que s et f soit pas nuls sinon retourne null
 * alloue dynamiquement la memoire a s len + 1 dans un pointeur result
 * verifie que l'allocation a fonctionne
 * parcours s et applique f a chaque char i en stockant le resultat dans result
 * ajoute carctere nul a result et retourne la chaine modifiee result
 */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h>

char ftft_tolower(unsigned int i, char c)
{
    (void)i;
    return (char)ft_tolower((int)c);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("usage : ./exec <string>\n");
		return (1);
	}

	char	*result;
	result = ft_strmapi(argv[1], ftft_tolower);
	if (!result)
	{
		printf("error in memory allocation\n");
		return (1);
	}
	printf("Result : '%s'\n", result);
	free(result);
	return (0);
}
*/
