/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:42:10 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:01:45 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* chercher derniere occurence de c dans str
 * si trouve on retourne un pointeur vers ce char dans str
 * on boucle toute la chaine pour que i a la position du caractere nul final
 * on cherche en reculant, si le caractere str[i] est c on retourne le pointeur
 * sinon on decremente i pour continuer jusqu'au debut de la chaine
 * si on ne trouve pas c dans str on retourne null
 */

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : ./exec <string> <char>\n");
		return (1);
	}
	
	const char	*str;
	char		*result;
	int		c;

	c = argv[2][0];
	str = argv[1];
	result = ft_strrchr(str, c);
	printf("Result : %s\n", result);
	return(0);
}
*/
