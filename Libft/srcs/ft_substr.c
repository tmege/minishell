/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:41:49 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 11:49:58 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	s est nul on retourne null
*	start plus loin que longueur de s on retourne "" vide
*	calcul substr_len, si depasse len on la reduit a len
*	memory allocation substr_len + caractere nul
*	copie des caracteres 1 par 1
*	terminaison de chaine par '\0' et retour pointeur substr
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	substr_len;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	substr_len = ft_strlen(s) - start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc(substr_len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[substr_len] = '\0';
	return (substr);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <string> <start> <len>\n");
		return (1);
	}
	const char	*str;
	unsigned int	start;
	size_t		len;
	char		*substr;
	
	str = argv[1];
	start = atoi(argv[2]);
	len = atoi(argv[3]);
	substr = ft_substr(str, start, len);
	if (substr)
	{
		printf("Substr : '%s'\n", substr);
		free(substr);
	}
	else
		printf("error, function returned null\n");
	return (0);
}
*/
