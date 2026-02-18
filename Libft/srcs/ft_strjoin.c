/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:17:12 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 17:05:33 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* concatene s1 et s2 dans str allouee dynamiquement
 * verifie si s1 ou s2 est nul, si un des deux oui on retourne null
 * alloue la memoire pour len s1 + len s2 + 1
 * verifie si l'allocation a reussi
 * copie s1 dans str
 * copie s2 a la suite de s1 dans str
 * ajoute caractere nul et retourne pointeur str
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	
	char	*joined;

	if (argc != 3)
	{
		printf("usage : ./exec <str1> <str2>\n");
		return (1);
	}
	joined = ft_strjoin(argv[1], argv[2]);
	if (!joined)
	{
		printf("memory allocation error\n");
		return (1);
	}
	printf("%s\n", joined);
	free(joined);
	return (0);
}
*/
