/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:37:01 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 16:08:47 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* cherche la premiere occurence d'un caractere ds une chaine de caracteres
 * faire tourner un i jusqu'a ce que le caractere a la position i soit egal a c
 * on cast &str[i] en char pour bien comparer les type
 * si on cherche le caractere nul on renvoie pointe vers fin de chaine
 * si c n'est pas trouve on retourne null
 */

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : <string> <char>\n");
		return (1);
	}
	
	char	*result;
	result = ft_strchr(argv[1], argv[2][0]);
	if (result)
		printf("char %c found at pos: %s", argv[2][0], result);
	else
		printf("char %c not found", argv[2][0]);
	return (0);
}
*/
